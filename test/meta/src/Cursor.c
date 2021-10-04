#include <meta.h>

#define test_ok(expr)\
    test_int((expr), 0)


void Cursor_set_bool() {
    ecs_world_t *world = ecs_init();

    ecs_bool_t value = false;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_bool_t), &value);
    test_ok( ecs_meta_set_bool(&cur, true) );

    test_bool(value, true);

    ecs_fini(world);
}

void Cursor_set_byte() {
    ecs_world_t *world = ecs_init();

    ecs_byte_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_byte_t), &value);
    test_ok( ecs_meta_set_uint(&cur, 20) );

    test_uint(value, 20);

    ecs_fini(world);
}

void Cursor_set_char() {
    ecs_world_t *world = ecs_init();

    ecs_char_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_char_t), &value);
    test_ok( ecs_meta_set_int(&cur, 20) );

    test_int(value, 20);

    ecs_fini(world);
}

void Cursor_set_i8() {
    ecs_world_t *world = ecs_init();

    ecs_i8_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_i8_t), &value);
    test_ok( ecs_meta_set_int(&cur, 20) );

    test_int(value, 20);

    ecs_fini(world);
}

void Cursor_set_i16() {
    ecs_world_t *world = ecs_init();

    ecs_i16_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_i16_t), &value);
    test_ok( ecs_meta_set_int(&cur, 20) );

    test_int(value, 20);

    ecs_fini(world);
}

void Cursor_set_i32() {
    ecs_world_t *world = ecs_init();

    ecs_i32_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_i32_t), &value);
    test_ok( ecs_meta_set_int(&cur, 20) );

    test_int(value, 20);

    ecs_fini(world);
}

void Cursor_set_i64() {
    ecs_world_t *world = ecs_init();

    ecs_i64_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_i64_t), &value);
    test_ok( ecs_meta_set_int(&cur, 20) );

    test_int(value, 20);

    ecs_fini(world);
}

void Cursor_set_iptr() {
    ecs_world_t *world = ecs_init();

    ecs_iptr_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_iptr_t), &value);
    test_ok( ecs_meta_set_int(&cur, 20) );

    test_int(value, 20);

    ecs_fini(world);
}

void Cursor_set_u8() {
    ecs_world_t *world = ecs_init();

    ecs_u8_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_u8_t), &value);
    test_ok( ecs_meta_set_uint(&cur, 20) );

    test_uint(value, 20);

    ecs_fini(world);
}

void Cursor_set_u16() {
    ecs_world_t *world = ecs_init();

    ecs_u16_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_u8_t), &value);
    test_ok( ecs_meta_set_uint(&cur, 20) );

    test_uint(value, 20);

    ecs_fini(world);
}

void Cursor_set_u32() {
    ecs_world_t *world = ecs_init();

    ecs_u32_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_u32_t), &value);
    test_ok( ecs_meta_set_uint(&cur, 20) );

    test_uint(value, 20);

    ecs_fini(world);
}

void Cursor_set_u64() {
    ecs_world_t *world = ecs_init();

    ecs_u64_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_u64_t), &value);
    test_ok( ecs_meta_set_uint(&cur, 20) );

    test_uint(value, 20);

    ecs_fini(world);
}

void Cursor_set_uptr() {
    ecs_world_t *world = ecs_init();

    ecs_uptr_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_uptr_t), &value);
    test_ok( ecs_meta_set_uint(&cur, 20) );

    test_uint(value, 20);

    ecs_fini(world);
}

void Cursor_set_float() {
    ecs_world_t *world = ecs_init();

    ecs_f32_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_f32_t), &value);
    test_ok( ecs_meta_set_float(&cur, 20.5) );

    test_flt(value, 20.5);

    ecs_fini(world);
}

void Cursor_set_double() {
    ecs_world_t *world = ecs_init();

    ecs_f64_t value = 10;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_f64_t), &value);
    test_ok( ecs_meta_set_float(&cur, 20.5) );

    test_flt(value, 20.5);

    ecs_fini(world);
}

void Cursor_set_string() {
    ecs_world_t *world = ecs_init();

    char *value = NULL;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_string_t), &value);
    test_ok( ecs_meta_set_string(&cur, "HelloWorld") );

    test_str(value, "HelloWorld");
    ecs_os_free(value);

    ecs_fini(world);
}

void Cursor_set_entity() {
    ecs_world_t *world = ecs_init();

    ecs_entity_t value = 0;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, ecs_id(ecs_entity_t), &value);
    test_ok( ecs_meta_set_entity(&cur, EcsFlecs) );

    test_uint(value, EcsFlecs);

    ecs_fini(world);
}

void Cursor_struct_set_i32() {
    typedef struct {
        ecs_i32_t x;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_i32_t)}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );

    test_int(value.x, 10);

    ecs_fini(world);
}

void Cursor_struct_set_i32_i32() {
    typedef struct {
        ecs_i32_t x;
        ecs_i32_t y;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_i32_t)},
            {"y", ecs_id(ecs_i32_t)}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 20) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.x, 10);
    test_int(value.y, 20);

    ecs_fini(world);
}

void Cursor_struct_set_i32_i32_i32() {
    typedef struct {
        ecs_i32_t x;
        ecs_i32_t y;
        ecs_i32_t z;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_i32_t)},
            {"y", ecs_id(ecs_i32_t)},
            {"z", ecs_id(ecs_i32_t)},
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 20) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 30) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.x, 10);
    test_int(value.y, 20);
    test_int(value.z, 30);

    ecs_fini(world);
}

void Cursor_struct_set_bool() {
    typedef struct {
        ecs_bool_t x;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_bool_t)}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );

    test_bool(value.x, true);

    ecs_fini(world);
}

void Cursor_struct_set_bool_bool() {
    typedef struct {
        ecs_bool_t x;
        ecs_bool_t y;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_bool_t)},
            {"y", ecs_id(ecs_bool_t)}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, false) );
    test_ok( ecs_meta_pop(&cur) );

    test_bool(value.x, true);
    test_bool(value.y, false);

    cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_bool(&cur, false) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_pop(&cur) );

    test_bool(value.x, false);
    test_bool(value.y, true);

    ecs_fini(world);
}

void Cursor_struct_set_bool_bool_bool() {
    typedef struct {
        ecs_bool_t x;
        ecs_bool_t y;
        ecs_bool_t z;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_bool_t)},
            {"y", ecs_id(ecs_bool_t)},
            {"z", ecs_id(ecs_bool_t)}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, false) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_pop(&cur) );

    test_bool(value.x, true);
    test_bool(value.y, false);
    test_bool(value.z, true);

    ecs_fini(world);
}

void Cursor_struct_set_bool_bool_i32_bool() {
    typedef struct {
        ecs_bool_t x;
        ecs_bool_t y;
        ecs_i32_t z;
        ecs_bool_t w;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_bool_t)},
            {"y", ecs_id(ecs_bool_t)},
            {"z", ecs_id(ecs_i32_t)},
            {"w", ecs_id(ecs_bool_t)},
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, false) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_pop(&cur) );

    test_bool(value.x, true);
    test_bool(value.y, false);
    test_int(value.z, 10);
    test_bool(value.w, true);

    ecs_fini(world);
}

void Cursor_struct_nested_i32() {
    typedef struct {
        ecs_i32_t x;
    } N1;

    typedef struct {
        N1 n_1;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t)}
        }
    });

    test_assert(n1 != 0);

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1.x, 10);

    ecs_fini(world);
}

void Cursor_struct_2_nested_1_i32_2_i32() {
    typedef struct {
        ecs_i32_t x;
    } N1;

    typedef struct {
        N1 n_1;
        N1 n_2;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t)}
        }
    });

    test_assert(n1 != 0);

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1},
            {"n_2", n1}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 20) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1.x, 10);
    test_int(value.n_2.x, 20);

    ecs_fini(world);
}

void Cursor_struct_2_nested_1_i32_i32_2_i32_i32() {
    typedef struct {
        ecs_i32_t x;
        ecs_i32_t y;
    } N1;

    typedef struct {
        N1 n_1;
        N1 n_2;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t)},
            {"y", ecs_id(ecs_i32_t)}
        }
    });

    test_assert(n1 != 0);

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1},
            {"n_2", n1}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 20) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 30) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 40) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1.x, 10);
    test_int(value.n_1.y, 20);
    test_int(value.n_2.x, 30);
    test_int(value.n_2.y, 40);

    ecs_fini(world);
}

void Cursor_struct_2_nested_1_i32_i32_2_i32_i32_w_padding_members() {
    typedef struct {
        ecs_i32_t x;
        ecs_i32_t y;
    } N1;

    typedef struct {
        bool p1;
        N1 n_1;
        bool p2;
        N1 n_2;
        bool p3;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t)},
            {"y", ecs_id(ecs_i32_t)}
        }
    });

    test_assert(n1 != 0);

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"p1", ecs_id(ecs_bool_t)},
            {"n_1", n1},
            {"p2", ecs_id(ecs_bool_t)},
            {"n_2", n1},
            {"p3", ecs_id(ecs_bool_t)},
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 10) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 20) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_push(&cur) );
    test_ok( ecs_meta_set_int(&cur, 30) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_int(&cur, 40) );
    test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_next(&cur) );
    test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_pop(&cur) );

    test_bool(value.p1, true);
    test_bool(value.p2, true);
    test_bool(value.p3, true);

    test_int(value.n_1.x, 10);
    test_int(value.n_1.y, 20);
    test_int(value.n_2.x, 30);
    test_int(value.n_2.y, 40);

    ecs_fini(world);
}

void Cursor_struct_set_array_i32_3() {
    typedef struct {
        ecs_i32_t x[3];
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_i32_t), 3}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_set_int(&cur, 10) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 20) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 30) );
        test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.x[0], 10);
    test_int(value.x[1], 20);
    test_int(value.x[2], 30);

    ecs_fini(world);
}

void Cursor_struct_set_2_array_i32_3() {
    typedef struct {
        ecs_i32_t x[3];
        ecs_i32_t y[3];
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"x", ecs_id(ecs_i32_t), 3},
            {"y", ecs_id(ecs_i32_t), 3}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_set_int(&cur, 10) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 20) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 30) );
        test_ok( ecs_meta_pop(&cur) );

        test_ok( ecs_meta_next(&cur) );

        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_set_int(&cur, 40) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 50) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 60) );
        test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.x[0], 10);
    test_int(value.x[1], 20);
    test_int(value.x[2], 30);

    test_int(value.y[0], 40);
    test_int(value.y[1], 50);
    test_int(value.y[2], 60);

    ecs_fini(world);
}

void Cursor_struct_set_2_array_i32_3_w_padding_members() {
    typedef struct {
        ecs_bool_t p1;
        ecs_i32_t x[3];
        ecs_bool_t p2;
        ecs_i32_t y[3];
        ecs_bool_t p3;
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"p1", ecs_id(ecs_bool_t)},
            {"x", ecs_id(ecs_i32_t), 3},
            {"p2", ecs_id(ecs_bool_t)},
            {"y", ecs_id(ecs_i32_t), 3},
            {"p3", ecs_id(ecs_bool_t)}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_set_bool(&cur, true) );
        test_ok( ecs_meta_next(&cur) );

        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_set_int(&cur, 10) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 20) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 30) );
        test_ok( ecs_meta_pop(&cur) );

        test_ok( ecs_meta_next(&cur) );
        test_ok( ecs_meta_set_bool(&cur, true) );
        test_ok( ecs_meta_next(&cur) );

        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_set_int(&cur, 40) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 50) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_set_int(&cur, 60) );
        test_ok( ecs_meta_pop(&cur) );

        test_ok( ecs_meta_next(&cur) );
        test_ok( ecs_meta_set_bool(&cur, true) );
    test_ok( ecs_meta_pop(&cur) );

    test_bool(value.p1, true);
    test_bool(value.p2, true);
    test_bool(value.p3, true);

    test_int(value.x[0], 10);
    test_int(value.x[1], 20);
    test_int(value.x[2], 30);

    test_int(value.y[0], 40);
    test_int(value.y[1], 50);
    test_int(value.y[2], 60);

    ecs_fini(world);
}

void Cursor_struct_set_array_w_struct_i32() {
    typedef struct {
        ecs_i32_t x;
    } N1;

    typedef struct {
        N1 n_1[3];
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t)}
        }
    });

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1, 3}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 10) );
            test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 20) );
            test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 30) );
            test_ok( ecs_meta_pop(&cur) );
        test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1[0].x, 10);
    test_int(value.n_1[1].x, 20);
    test_int(value.n_1[2].x, 30);

    ecs_fini(world);
}

void Cursor_struct_set_2_array_w_struct_i32() {
    typedef struct {
        ecs_i32_t x;
    } N1;

    typedef struct {
        N1 n_1[3];
        N1 n_2[3];
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t)}
        }
    });

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1, 3},
            {"n_2", n1, 3}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 10) );
            test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 20) );
            test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 30) );
            test_ok( ecs_meta_pop(&cur) );
        test_ok( ecs_meta_pop(&cur) );

        test_ok( ecs_meta_next(&cur) );

        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 40) );
            test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 50) );
            test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_next(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_set_int(&cur, 60) );
            test_ok( ecs_meta_pop(&cur) );
        test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1[0].x, 10);
    test_int(value.n_1[1].x, 20);
    test_int(value.n_1[2].x, 30);

    test_int(value.n_2[0].x, 40);
    test_int(value.n_2[1].x, 50);
    test_int(value.n_2[2].x, 60);

    ecs_fini(world);
}

void Cursor_struct_set_array_w_struct_w_array_i32() {
    typedef struct {
        ecs_i32_t x[3];
    } N1;

    typedef struct {
        N1 n_1[3];
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t), 3}
        }
    });

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1, 3}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 10) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 11) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 12) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );

            test_ok( ecs_meta_next(&cur) );

            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 20) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 21) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 22) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );

            test_ok( ecs_meta_next(&cur) );

            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 30) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 31) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 32) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );
        test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1[0].x[0], 10);
    test_int(value.n_1[0].x[1], 11);
    test_int(value.n_1[0].x[2], 12);

    test_int(value.n_1[1].x[0], 20);
    test_int(value.n_1[1].x[1], 21);
    test_int(value.n_1[1].x[2], 22);

    test_int(value.n_1[2].x[0], 30);
    test_int(value.n_1[2].x[1], 31);
    test_int(value.n_1[2].x[2], 32);

    ecs_fini(world);
}

void Cursor_struct_set_2_array_w_struct_w_array_i32() {
    typedef struct {
        ecs_i32_t x[3];
    } N1;

    typedef struct {
        N1 n_1[3];
        N1 n_2[3];
    } T;

    ecs_world_t *world = ecs_init();

    ecs_entity_t n1 = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "N1",
        .members = {
            {"x", ecs_id(ecs_i32_t), 3}
        }
    });

    ecs_entity_t t = ecs_struct_init(world, &(ecs_struct_desc_t) {
        .entity.name = "T",
        .members = {
            {"n_1", n1, 3},
            {"n_2", n1, 3}
        }
    });

    test_assert(t != 0);

    T value;

    ecs_meta_cursor_t cur = ecs_meta_cursor(world, t, &value);
    test_ok( ecs_meta_push(&cur) );
        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 10) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 11) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 12) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );

            test_ok( ecs_meta_next(&cur) );

            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 20) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 21) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 22) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );

            test_ok( ecs_meta_next(&cur) );

            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 30) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 31) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 32) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );
        test_ok( ecs_meta_pop(&cur) );

        test_ok( ecs_meta_next(&cur) );

        test_ok( ecs_meta_push(&cur) );
            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 40) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 41) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 42) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );

            test_ok( ecs_meta_next(&cur) );

            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 50) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 51) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 52) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );

            test_ok( ecs_meta_next(&cur) );

            test_ok( ecs_meta_push(&cur) );
                test_ok( ecs_meta_push(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 60) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 61) );
                    test_ok( ecs_meta_next(&cur) );
                    test_ok( ecs_meta_set_int(&cur, 62) );
                test_ok( ecs_meta_pop(&cur) );
            test_ok( ecs_meta_pop(&cur) );
        test_ok( ecs_meta_pop(&cur) );
    test_ok( ecs_meta_pop(&cur) );

    test_int(value.n_1[0].x[0], 10);
    test_int(value.n_1[0].x[1], 11);
    test_int(value.n_1[0].x[2], 12);

    test_int(value.n_1[1].x[0], 20);
    test_int(value.n_1[1].x[1], 21);
    test_int(value.n_1[1].x[2], 22);

    test_int(value.n_1[2].x[0], 30);
    test_int(value.n_1[2].x[1], 31);
    test_int(value.n_1[2].x[2], 32);

    test_int(value.n_2[0].x[0], 40);
    test_int(value.n_2[0].x[1], 41);
    test_int(value.n_2[0].x[2], 42);

    test_int(value.n_2[1].x[0], 50);
    test_int(value.n_2[1].x[1], 51);
    test_int(value.n_2[1].x[2], 52);

    test_int(value.n_2[2].x[0], 60);
    test_int(value.n_2[2].x[1], 61);
    test_int(value.n_2[2].x[2], 62);

    ecs_fini(world);
}