#include <stddef.h>
#include "basic_obj.h"
#include "matrix.h"
#include "cst_types.h"

void add_vertices(struct Basic_Obj *obj, float vertices[], size_t vertices_size) {
    //Create a vbo using passed in vertices.
    glGenBuffers(1, &obj->vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(vertces[0]), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void get_model_mat(struct Basic_Obj *obj, struct Mat4 *mat) {
    *mat = {0}; //Back to normal
    //Apply the translation
    

    //Apply the orientation / rotation

    //Apply the scale

}

void draw_object(struct Basic_Obj *obj) {

}
