#pragma once
#include <stddef.h>
#include "matrix.h"
#include "cst_types.h"

struct Basic_Obj {
    GLuint vertex_vbo;
    GLuint vao;
    GLuint index_buffer;
    Vec3 offset;
    Vec3 scale;
    Vec3 rotation;
};

void add_vertices(struct Basic_Obj *obj, float vertices[], size_t vertices_size);
void get_model_mat(struct Mat4 mat);
void draw_object(struct Basic_Obj *obj);
