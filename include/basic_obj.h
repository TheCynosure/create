#pragma once
#include <GL/glew.h>
#include <stddef.h>
#include <cglm/cglm.h>

struct Basic_Obj {
    GLuint vertex_vbo;
    GLuint vao;
    GLuint index_buffer;
    size_t index_buffer_size;
    vec3 offset;
    vec3 scale;
    vec3 rotation;
    float model_mat[16];
};

void add_vertices(struct Basic_Obj *obj, float vertices[], size_t vertices_size);
void add_indices(struct Basic_Obj *obj, GLshort indices[], size_t indices_size);
void add_vao(struct Basic_Obj *obj, size_t color_data_offset);
void get_model_mat(struct Basic_Obj *obj);
void draw_object(struct Basic_Obj *obj, GLuint program_id);
