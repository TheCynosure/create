#include <stddef.h>
#include <cglm/cglm.h>
#include "basic_obj.h"

void add_vertices(struct Basic_Obj *obj, float vertices[], size_t vertices_size) {
    //Create a vbo using passed in vertices.
    glGenBuffers(1, &obj->vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void add_indices(struct Basic_Obj *obj, GLshort indices[], size_t indices_size) {
    glGenBuffers(1, &obj->index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(indices[0]), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    obj->index_buffer_size = indices_size;
}

void add_vao(struct Basic_Obj *obj, size_t color_data_offset) {
    //Generate a vao.
    glGenVertexArrays(1, &obj->vao);
    glBindVertexArray(obj->vao);

    glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //Vertices
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_data_offset); //Colors
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->index_buffer);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void get_model_mat(struct Basic_Obj *obj) {
    //Apply the translation
    mat4 mat = GLM_MAT4_IDENTITY_INIT;
    glm_translate(mat, (vec3){obj->offset[0], obj->offset[1], obj->offset[2]});

    //Apply the orientation / rotation
    glm_rotate(mat, obj->rotation[2], (vec3){0.0f, 0.0f, 1.0f});
    glm_rotate(mat, obj->rotation[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(mat, obj->rotation[0], (vec3){1.0f, 0.0f, 0.0f});

    //Apply the scale
    mat4 scale = GLM_MAT4_IDENTITY_INIT;
    glm_scale(scale, obj->scale);

    mat4 final = GLM_MAT4_IDENTITY_INIT;
    glm_mul(mat, scale, final);

    for(int c = 0; c < 4; c++) {
        for(int r = 0; r < 4; r++) {
            obj->model_mat[r * 4 + c] = final[r][c];
        }
    }
}

void draw_object(struct Basic_Obj *obj, GLuint program_id) {
    GLuint model_mat_uniform = glGetUniformLocation(program_id, "model_view_mat");
    get_model_mat(obj);
    glBindVertexArray(obj->vao);
    glUniformMatrix4fv(model_mat_uniform, 1, GL_FALSE, obj->model_mat);
    glDrawElements(GL_TRIANGLES, obj->index_buffer_size, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}
