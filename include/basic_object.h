#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include "matrix.h"

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    GLuint vertex_vbo;
    GLuint vao;
    GLuint index_buffer;
    Vec3 offset;
    Vec3 scale;
    Vec3 rotation;
} Basic_Obj;

void add_vertices(Basic_Obj *obj, float vertices, size_i size)
void get_model_mat(Mat4 mat);
void draw_object(Basic_Obj *obj);

#endif

