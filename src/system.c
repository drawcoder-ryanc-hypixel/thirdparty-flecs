#include <assert.h>
#include <string.h>
#include "include/private/flecs.h"
#include "include/util/time.h"

static
void match_type(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t system,
    EcsRowSystem *system_data,
    ecs_type_t type)
{
    /* Test if the components of the system are equal or a subset of the 
     * components of the type */
    ecs_entity_t match = ecs_type_contains(
        world, stage, type, system_data->base.and_from_entity, true, false);

    /* If there is a match, add the system to the type-row_system index */
    if (match) {
        ecs_map_t *index = NULL;
        EcsSystemKind kind = system_data->base.kind;

        if (kind == EcsOnAdd) {
            index = world->type_sys_add_index;
        } else if (kind == EcsOnRemove) {
            index = world->type_sys_remove_index;
        } else if (kind == EcsOnSet) {
            index = world->type_sys_set_index;
        } else {
            ecs_abort(ECS_INVALID_PARAMETERS, NULL);
        }

        ecs_vector_t *systems = ecs_map_get(index, type);
        if (!systems) {
            systems = ecs_vector_new(&handle_arr_params, 1);
        }

        ecs_entity_t *new_elem = ecs_vector_add(&systems, &handle_arr_params);
        *new_elem = system;

        /* Always set the system entry, as array may have been realloc'd */
        ecs_map_set(index, type, systems);
    }
}

/* Match system against existing families to build the type-rowsys index */
static
void match_families(
    ecs_world_t *world,
    ecs_entity_t system,
    EcsRowSystem *system_data)
{
    EcsIter it = ecs_map_iter(world->main_stage.type_index);

    /* Iterating over a map is a bit slow, but this only happens when a new
     * row system is created, which is very infrequent. */
    while (ecs_iter_hasnext(&it)) {
        uint64_t key; /* Only interested in the key, which is the type hash */
        ecs_map_next(&it, &key);

        ecs_type_t type = key;
        
        match_type(world, NULL, system, system_data, type);
    }
}

static
bool has_refs(
    EcsSystem *system_data)
{
    uint32_t i, count = ecs_vector_count(system_data->columns);
    ecs_system_column_t *columns = ecs_vector_first(system_data->columns);

    for (i = 0; i < count; i ++) {
        ecs_system_expr_elem_kind_t elem_kind = columns[i].kind;

        if (columns[i].oper_kind == EcsOperNot && elem_kind == EcsFromId) {
            /* Special case: if oper kind is Not and the query contained a
             * shared expression, the expression is translated to FromId to
             * prevent resolving the ref */
            return true;
        } else if (elem_kind != EcsFromSelf && elem_kind != EcsFromId) {
            /* If the component is not from the entity being iterated over, and
             * the column is not just passing an id, it must be a reference to
             * another entity. */
            return true;
        }
    }

    return false;
}

/** Create a new row system. A row system is a system executed on a single row,
 * typically as a result of a ADD, REMOVE or SET trigger.
 */
static
ecs_entity_t new_row_system(
    ecs_world_t *world,
    const char *id,
    EcsSystemKind kind,
    bool needs_tables,
    const char *sig,
    ecs_system_action_t action)
{
    uint32_t count = ecs_columns_count(sig);
    if (!count) {
        return 0;
    }

    ecs_entity_t result = _ecs_new(world, world->t_row_system);

    EcsId *id_data = ecs_get_ptr(world, result, EcsId);
    ecs_assert(id_data != NULL, ECS_INTERNAL_ERROR, NULL);

    *id_data = id;

    EcsRowSystem *system_data = ecs_get_ptr(world, result, EcsRowSystem);
    memset(system_data, 0, sizeof(EcsRowSystem));
    system_data->base.action = action;
    system_data->base.signature = sig;
    system_data->base.enabled = true;
    system_data->base.kind = kind;
    system_data->base.cascade_by = 0;
    system_data->components = ecs_vector_new(&handle_arr_params, count);

    if (ecs_parse_component_expr(
        world, sig, ecs_parse_component_action, system_data) != 0)
    {
        ecs_abort(ECS_INVALID_COMPONENT_EXPRESSION, sig);
    }

    ecs_type_t type_id = 0;
    uint32_t i, column_count = ecs_vector_count(system_data->base.columns);
    ecs_system_column_t *buffer = ecs_vector_first(system_data->base.columns);

    for (i = 0; i < column_count; i ++) {
        ecs_entity_t *h = ecs_vector_add(
            &system_data->components, &handle_arr_params);

        ecs_system_column_t *column = &buffer[i];
        *h = column->is.component;

        if (column->kind != EcsFromId) {
            type_id = ecs_type_add(
                world, NULL, type_id, column->is.component);
        }
    }

    ecs_entity_t *elem = NULL;

    if (!needs_tables) {
        if (kind == EcsOnUpdate) {
            elem = ecs_vector_add(&world->tasks, &handle_arr_params);
        } else if (kind == EcsOnRemove) {
            elem = ecs_vector_add(&world->fini_tasks, &handle_arr_params);
        }
    } else {
        if (kind == EcsOnAdd) {
            elem = ecs_vector_add(&world->add_systems, &handle_arr_params);
        } else if (kind == EcsOnRemove) {
            elem = ecs_vector_add(&world->remove_systems, &handle_arr_params);
        } else if (kind == EcsOnSet) {
            elem = ecs_vector_add(&world->set_systems, &handle_arr_params);
        }
    }

    if (elem) {
        *elem = result;
    }

    ecs_system_compute_and_families(world, &system_data->base);

    if (needs_tables) {
        match_families(world, result, system_data);
    }

    return result;
}

/* -- Private API -- */

void ecs_system_compute_and_families(
    ecs_world_t *world,
    EcsSystem *system_data)
{
    uint32_t i, column_count = ecs_vector_count(system_data->columns);
    ecs_system_column_t *buffer = ecs_vector_first(system_data->columns);

    for (i = 0; i < column_count; i ++) {
        ecs_system_column_t *elem = &buffer[i];
        ecs_system_expr_elem_kind_t elem_kind = elem->kind;
        ecs_system_expr_oper_kind_t oper_kind = elem->oper_kind;

        if (elem_kind == EcsFromSelf) {
            if (oper_kind == EcsOperAnd) {
                system_data->and_from_entity = ecs_type_add(
                 world, NULL, system_data->and_from_entity, elem->is.component);
            }
        } else if (elem_kind == EcsFromSystem) {
            if (oper_kind == EcsOperAnd) {
                system_data->and_from_system = ecs_type_add(
                  world, NULL, system_data->and_from_system, elem->is.component);
            }
        } else if (elem_kind == EcsCascade) {
            system_data->cascade_by = i + 1;
        }
    }
}

/** Parse callback that adds component to the components array for a system */
int ecs_parse_component_action(
    ecs_world_t *world,
    ecs_system_expr_elem_kind_t elem_kind,
    ecs_system_expr_oper_kind_t oper_kind,
    const char *component_id,
    const char *source_id,
    void *data)
{
    EcsSystem *system_data = data;
    ecs_system_column_t *elem;

    /* Lookup component handly by string identifier */
    ecs_entity_t component = ecs_lookup(world, component_id);
    if (!component) {
        /* "0" is a valid expression used to indicate that a system matches no
         * components */
        if (strcmp(component_id, "0")) {
            ecs_abort(ECS_INVALID_COMPONENT_ID, component_id);
        } else {
            /* Don't add 0 component to signature */
            return 0;
        }
    }

    /* If retrieving a component from a system, only the AND operator is
     * supported. The set of system components is expected to be constant, and
     * thus no conditional operators are needed. */
    if (elem_kind == EcsFromSystem && oper_kind != EcsOperAnd) {
        ecs_abort(ECS_INVALID_COMPONENT_EXPRESSION, 0);
    }

    /* AND (default) and optional columns are stored the same way */
    if (oper_kind == EcsOperAnd || oper_kind == EcsOperOptional) {
        elem = ecs_vector_add(&system_data->columns, &column_arr_params);
        elem->kind = elem_kind;
        elem->oper_kind = oper_kind;
        elem->is.component = component;

        if (elem_kind == EcsFromEntity) {
            elem->source = ecs_lookup(world, source_id);
            if (!elem->source) {
                ecs_abort(ECS_UNRESOLVED_IDENTIFIER, source_id);
            }

            ecs_set_watching(world, elem->source, true);
        }

    /* OR columns store a type id instead of a single component */
    } else if (oper_kind == EcsOperOr) {
        elem = ecs_vector_last(system_data->columns, &column_arr_params);
        if (elem->oper_kind == EcsOperAnd) {
            elem->is.type = ecs_type_add(
                world, NULL, 0, elem->is.component);
        } else {
            if (elem->kind != elem_kind) {
                /* Cannot mix FromEntity and FromComponent in OR */
                goto error;
            }
        }

        elem->is.type = ecs_type_add(
            world, NULL, elem->is.type, component);
        elem->kind = elem_kind;
        elem->oper_kind = EcsOperOr;

    /* A system stores two NOT familes; one for entities and one for components.
     * These can be quickly & efficiently used to exclude tables with
     * ecs_type_contains. */
    } else if (oper_kind == EcsOperNot) {
        elem = ecs_vector_add(&system_data->columns, &column_arr_params);
        elem->kind = EcsFromId; /* Just pass handle to system */
        elem->oper_kind = EcsOperNot;
        elem->is.component = component;

        if (elem_kind == EcsFromSelf) {
            system_data->not_from_entity =
                ecs_type_add(
                    world, NULL, system_data->not_from_entity, component);
        } else {
            system_data->not_from_component =
              ecs_type_add(
                  world, NULL, system_data->not_from_component, component);
        }
    }

    return 0;
error:
    return -1;
}

/** Run system on a single row */
ecs_type_t ecs_notify_row_system(
    ecs_world_t *world,
    ecs_entity_t system,
    ecs_vector_t *type,
    ecs_table_t *table,
    ecs_table_column_t *table_columns,
    uint32_t offset,
    uint32_t limit)
{
    ecs_entity_info_t info = {.entity = system};

    ecs_world_t *real_world = world;
    if (world->magic == ECS_THREAD_MAGIC) {
        real_world = ((ecs_thread_t*)world)->world; /* dispel the magic */
    }

    EcsRowSystem *system_data = ecs_get_ptr_intern(
        real_world, &real_world->main_stage, &info, EEcsRowSystem, false, true);
    
    assert(system_data != NULL);

    if (!system_data->base.enabled) {
        return false;
    }

    ecs_system_action_t action = system_data->base.action;

    uint32_t i, column_count = ecs_vector_count(system_data->base.columns);
    ecs_system_column_t *buffer = ecs_vector_first(system_data->base.columns);
    int32_t *columns = ecs_os_alloca(int32_t, column_count);
    ecs_reference_t *references = ecs_os_alloca(ecs_reference_t, column_count);

    uint32_t ref_id = 0;

    /* Iterate over system columns, resolve data from table or references */

    for (i = 0; i < column_count; i ++) {
        if (buffer[i].kind == EcsFromSelf) {
            /* If a regular column, find corresponding column in table */
            columns[i] = ecs_type_index_of(type, buffer[i].is.component) + 1;
        } else {
            /* If not a regular column, it is a reference */
            ecs_entity_t entity = 0;
            ecs_entity_t component = buffer[i].is.component;

            /* Resolve component from the right source */
            
            if (buffer[i].kind == EcsFromSystem) {
                /* The source is the system itself */
                entity = system;
            } else if (buffer[i].kind == EcsFromSingleton) {
                /* The source is the world's singleton entity */
                entity = 0;         
            } else if (buffer[i].kind == EcsFromEntity) {
                /* The source is another entity (prefab, container, other) */
                entity = buffer[i].source;
            }

            /* Store the reference data so the system callback can access it */
            info = (ecs_entity_info_t){.entity = entity};
            references[ref_id] = (ecs_reference_t){
                .entity = entity, 
                .component = component,
                .cached_ptr = ecs_get_ptr_intern(real_world, &real_world->main_stage, 
                                &info, component, false, true)
            };

            /* Update the column vector with the entry to the ref vector */
            ref_id ++;
            columns[i] = -ref_id;
        }
    }

    /* Prepare ecs_rows_t for system callback */
    ecs_rows_t rows = {
        .world = world,
        .system = system,
        .columns = columns,
        .column_count = ecs_vector_count(system_data->components),
        .table = table,
        .table_columns = table_columns,
        .components = ecs_vector_first(system_data->components),
        .frame_offset = 0,
        .offset = offset,
        .count = limit
    };

    /* Set references metadata if system has references */
    if (ref_id) {
        rows.references = references;
    }

    /* Obtain pointer to vector with entity identifiers */
    if (table_columns) {
        ecs_entity_t *entities = ecs_vector_first(table_columns[0].data);
        rows.entities = &entities[rows.offset];
    }

    /* Run system */
    action(&rows);

    /* Return the components that the system promised to init/read/fini */
    return system_data->base.and_from_entity;
}

/** Run a task. A task is a system that contains no columns that can be matched
 * against a table. Examples of such columns are EcsFromSystem or EcsFromId.
 * Tasks are ran once every frame. */
void ecs_run_task(
    ecs_world_t *world,
    ecs_entity_t system)
{
    ecs_notify_row_system(world, system, NULL, NULL, NULL, 0, 1);
}

/* Notify row system of a new type */
void ecs_row_system_notify_of_type(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_entity_t system,
    ecs_type_t type)
{
    EcsRowSystem *system_data = ecs_get_ptr(world, system, EcsRowSystem);

    match_type(world, stage, system, system_data, type);
}

/* -- Public API -- */

ecs_entity_t ecs_new_system(
    ecs_world_t *world,
    const char *id,
    EcsSystemKind kind,
    const char *sig,
    ecs_system_action_t action)
{
    ecs_entity_t result = ecs_lookup(world, id);
    if (result) {
        return result;
    }

    bool needs_tables = ecs_needs_tables(world, sig);

    if (!needs_tables && (kind == EcsOnAdd ||
        kind == EcsOnSet))
    {
        ecs_abort(ECS_INVALID_PARAMETERS, 0);
    }

    if (needs_tables && (kind == EcsOnLoad ||
                         kind == EcsPreUpdate || kind == EcsOnUpdate ||
                         kind == EcsOnValidate || kind == EcsPostUpdate ||
                         kind == EcsPreStore || kind == EcsOnStore ||
                         kind == EcsManual))
    {
        result = ecs_new_col_system(world, id, kind, sig, action);
    } else if (!needs_tables ||
        (kind == EcsOnAdd || kind == EcsOnRemove || kind == EcsOnSet))
    {
        result = new_row_system(world, id, kind, needs_tables, sig, action);
    } else {
        ecs_abort(ECS_INVALID_PARAMETERS, 0);
    }

    EcsSystem *system_data = ecs_get_ptr(world, result, EcsColSystem);
    if (!system_data) {
        system_data = _ecs_get_ptr(world, result, TEcsRowSystem);
        if (!system_data) {
            ecs_abort(ECS_INTERNAL_ERROR, NULL);
        }
    }

    system_data->has_refs = has_refs(system_data);

    /* If system contains FromSystem params, add them tot the system */
    if (system_data->and_from_system) {
        ecs_vector_t *f = ecs_type_get(world, NULL, system_data->and_from_system);
        ecs_entity_t *buffer = ecs_vector_first(f);
        uint32_t i, count = ecs_vector_count(f);
        for (i = 0; i < count; i ++) {
            ecs_type_t type = ecs_type_from_entity(world, buffer[i]);
            _ecs_add(world, result, type);
        }
    }

    return result;
}

void ecs_enable(
    ecs_world_t *world,
    ecs_entity_t system,
    bool enabled)
{
    assert(world->magic == ECS_WORLD_MAGIC);
    bool col_system = false;

    /* Try to get either ColSystem or RowSystem data */
    EcsSystem *system_data = ecs_get_ptr(world, system, EcsColSystem);
    if (!system_data) {
        system_data = ecs_get_ptr(world, system, EcsRowSystem);
    } else {
        col_system = true;
    }

    /* If entity is neither ColSystem nor RowSystem, it should be a type */
    if (!system_data) {
        EcsTypeComponent *type_data = ecs_get_ptr(
            world, system, EcsTypeComponent);

        assert(type_data != NULL);

        ecs_world_t *world_temp = world;
        ecs_stage_t *stage = ecs_get_stage(&world_temp);
        ecs_vector_t *type = ecs_type_get(world, stage, type_data->type);
        ecs_entity_t *buffer = ecs_vector_first(type);
        uint32_t i, count = ecs_vector_count(type);
        for (i = 0; i < count; i ++) {
            /* Enable/disable all systems in type */
            ecs_enable(world, buffer[i], enabled);
        }
    } else {
        if (col_system) {
            EcsColSystem *col_system = (EcsColSystem*)system_data;
            if (enabled) {
                if (!system_data->enabled) {
                    if (ecs_vector_count(col_system->tables)) {
                        ecs_world_activate_system(
                            world, system, col_system->base.kind, true);
                    }
                }
            } else {
                if (system_data->enabled) {
                    if (ecs_vector_count(col_system->tables)) {
                        ecs_world_activate_system(
                            world, system, col_system->base.kind, false);
                    }
                }
            }
        }

        system_data->enabled = enabled;
    }
}

bool ecs_is_enabled(
    ecs_world_t *world,
    ecs_entity_t system)
{
    EcsSystem *system_data = ecs_get_ptr(world, system, EcsColSystem);
    if (!system_data) {
        system_data = ecs_get_ptr(world, system, EcsRowSystem);
    }

    if (system_data) {
        return system_data->enabled;
    } else {
        return true;
    }
}

void ecs_set_period(
    ecs_world_t *world,
    ecs_entity_t system,
    float period)
{
    assert(world->magic == ECS_WORLD_MAGIC);
    EcsColSystem *system_data = ecs_get_ptr(world, system, EcsColSystem);
    if (system_data) {
        system_data->period = period;
    }
}

void* _ecs_column(
    ecs_rows_t *rows,
    uint32_t index,
    bool test)
{
    if (index > rows->column_count) {
        ecs_assert(test, ECS_COLUMN_INDEX_OUT_OF_RANGE, NULL);
        return NULL;
    }

    int32_t table_column;

    if (index == 0) {
        table_column = 0;
    } else {
        if (!rows->columns) {
            ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
            return NULL;
        }

        table_column = rows->columns[index - 1];
        if (!table_column) {
            ecs_assert(test, ECS_COLUMN_IS_NOT_SET, NULL);
            return NULL;
        }
    }

    if (table_column < 0) {
        ecs_assert(test, ECS_COLUMN_IS_SHARED, NULL);
        return NULL;
    }

    if (!rows->table_columns) {
        ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
        return NULL;
    }

    ecs_table_column_t *column = &((ecs_table_column_t*)rows->table_columns)[table_column];
    void *buffer = ecs_vector_first(column->data);
    return ECS_OFFSET(buffer, column->size * rows->offset);
}

void* _ecs_shared(
    ecs_rows_t *rows,
    uint32_t index,
    bool test)
{
    if (index > rows->column_count) {
        ecs_assert(test, ECS_COLUMN_INDEX_OUT_OF_RANGE, NULL);
        return NULL;
    }
    
    int32_t table_column;

    if (index == 0) {
        return 0;
    } else {
        if (!rows->columns) {
            ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
            return NULL;
        }

        table_column = rows->columns[index - 1];
        if (table_column >= 0) {
            ecs_assert(test, ECS_COLUMN_IS_NOT_SHARED, NULL);
            return NULL;
        }

        if (!rows->references) {
            ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
            return NULL;
        }

        return rows->references[-table_column - 1].cached_ptr;
    }
}

ecs_entity_t _ecs_column_source(
    ecs_rows_t *rows,
    uint32_t index,
    bool test)
{
    if (index > rows->column_count) {
        return 0;
    }

    if (index == 0) {
        return 0;
    } else {
        if (!rows->columns) {
            ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
            return 0;
        }

        int32_t table_column = rows->columns[index - 1];
        if (table_column >= 0) {
            return 0;
        }

        ecs_assert(rows->references != NULL, ECS_INTERNAL_ERROR, NULL);

        ecs_reference_t *ref = &rows->references[-table_column - 1];
        return ref->entity;
    }
}

ecs_type_t _ecs_column_type(
    ecs_rows_t *rows,
    uint32_t index,
    bool test)
{
    if (index == 0) {
        return 0;
    } else if (index > rows->column_count) {
        return 0;
    } else {
        if (!rows->components) {
            ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
            return 0;
        }

        ecs_entity_t component = rows->components[index - 1];
        return ecs_type_from_entity(rows->world, component);
    }
}

ecs_entity_t _ecs_column_entity(
    ecs_rows_t *rows,
    uint32_t index,
    bool test)
{
    if (index == 0) {
        return 0;
    } else if (index > rows->column_count) {
        return 0; 
    } else {
        if (!rows->components) {
            ecs_assert(test, ECS_INTERNAL_ERROR, NULL);
            return 0;
        }
        return rows->components[index - 1];
    }  
}

void *_ecs_field(
    ecs_rows_t *rows, 
    uint32_t index, 
    uint32_t column,
    bool test)
{
    if (column > rows->column_count) {
        ecs_assert(test, ECS_COLUMN_INDEX_OUT_OF_RANGE, NULL);
        return NULL;
    }

    int32_t table_column;

    if (column == 0) {
        table_column = 0;
    } else {
        ecs_assert(rows->columns != NULL, ECS_INTERNAL_ERROR, NULL);
        table_column = rows->columns[column - 1];

        if (!table_column) {
            return NULL;
        }
    }

    if (table_column < 0) {
        ecs_assert(rows->references != NULL, ECS_INTERNAL_ERROR, NULL);
        return rows->references[-table_column - 1].cached_ptr;
    } else {
        ecs_assert(rows->table_columns != NULL, ECS_INTERNAL_ERROR, NULL);
        ecs_table_column_t *column = &((ecs_table_column_t*)rows->table_columns)[table_column];

#ifndef NDEBUG
        ecs_assert(index < ecs_vector_count(column->data), ECS_OUT_OF_RANGE, 0);
#endif

        void *buffer = ecs_vector_first(column->data);
        return ECS_OFFSET(buffer, column->size * (index + rows->offset));
    }
}
