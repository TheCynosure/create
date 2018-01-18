#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include "render.h"
#include "loader.h"
#include "matrix.h"
#include "cst_types.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))
#define NUM_OF_VERT 36

static float *vertex_pos;
static GLshort element_array[] = {
	0, 2, 1,
	3, 2, 0,
	4, 5, 6,
	6, 7, 4,
	8, 9, 10,
	11, 13, 12,
	14, 16, 15,
	17, 16, 14,
};

Obj simple_obj;
Obj simple_obj_2;
GLuint shader_program;
GLuint model_mat_uniform;
float offset = 0.0f;

void render_init(GLuint programID) {
    shader_program = programID;

    //Load up the vertex data
    size_t vertex_size;
    vertex_pos = load_general_format_verts("data/wedge.verts", &vertex_size);

    //TODO: Move all the below stuff into the Basic Object file
    //Generate a vertex buffer based on our vertex_pos array
    glGenBuffers(1, &simple_obj.vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, simple_obj.vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_pos), vertex_pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Generate a Element buffer
    glGenBuffers(1, &simple_obj.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_obj.index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_array), element_array, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Generate a vao.
    glGenVertexArrays(1, &simple_obj.vertex_vao);
    glBindVertexArray(simple_obj.vertex_vao);

    size_t color_data_offset = NUM_OF_VERT * 4 * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, simple_obj.vertex_vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_data_offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_obj.index_buffer);
    glBindVertexArray(0);

    glGenVertexArrays(1, &simple_obj_2.vertex_vao);
    glBindVertexArray(simple_obj_2.vertex_vao);

    simple_obj_2.vertex_vbo = simple_obj.vertex_vbo;
    simple_obj_2.index_buffer = simple_obj.index_buffer;

    size_t pos_data_offset = sizeof(float) * 4 * (NUM_OF_VERT / 2);
    color_data_offset += sizeof(float) * 4 * (NUM_OF_VERT / 2);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)pos_data_offset);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_data_offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simple_obj_2.index_buffer);
    glBindVertexArray(0);

    //Get the offset uniform location.
    model_mat_uniform = glGetUniformLocation(programID, "model_view_mat");

    //Enable Culling of back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    //Enable the Depth Buffer and Testing method
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDepthRange(0.0f, 1.0f);

    free(vertex_pos);
}

void render_main(void) {
    set_scale(&simple_obj_2.translation_mat, (struct Vec3){1.0f, fabs(sin(offset)), 1.0f});
    set_translation(&simple_obj_2.translation_mat, (struct Vec3){0.0f, 0.0f, -5.0f});
    set_translation(&simple_obj.translation_mat, (struct Vec3){cos(offset) * 2, sin(offset) * 2, -5.0f});
    offset += 0.01;

    //Clear the Screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Turn on the Shaders
    glUseProgram(shader_program);

    glBindVertexArray(simple_obj.vertex_vao);
    glUniformMatrix4fv(model_mat_uniform, 1, GL_FALSE, simple_obj.translation_mat.m);
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(element_array), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(simple_obj_2.vertex_vao);
    glUniformMatrix4fv(model_mat_uniform, 1, GL_FALSE, simple_obj_2.translation_mat.m);
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(element_array), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);

    //End the shader program
    glUseProgram(0);

    glutSwapBuffers();
    glutPostRedisplay();
}
