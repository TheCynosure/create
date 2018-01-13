#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include "render.h"
#include "loader.h"

#define NUM_OF_VERT 36

typedef struct {
    GLuint vertex_vbo;
    GLuint vertex_vao;
    GLuint index_buffer;
} Obj;

static float vertex_pos[288];
static float element_array[0];
Obj simple_obj;
Obj simple_obj_2;
GLuint shader_program;
GLuint offset_uniform;

void render_init(GLuint programID) {
    shader_program = programID;

    //Load up the vertex data
    load_general_verts(vertex_pos, "data/rect.verts");

    //Generate a vertex buffer based on our vertex_pos array
    glGenBuffers(1, &simple_obj.vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, simple_obj.vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_pos), vertex_pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //Generate a Element buffer
    glGenBuffers(1, &simple_obj.index_buffer);
    //TODO

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
    offset_uniform = glGetUniformLocation(programID, "offset");

    //Enable Culling of back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
}

void render_main(void) {
    //Clear the Screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Turn on the Shaders
    glUseProgram(shader_program);

    glBindVertexArray(simple_obj.vertex_vao);
    glUniform3f(offset_uniform, 0.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(simple_obj.index_buffer), GL_UNSIGNED_SHORT, 0);
    
    glBindVertexArray(simple_obj_2.vertex_vao);
    glUniform3f(offset_uniform, 0.0f, 0.0f, -1.0f);
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(simple_obj_2.index_buffer), GL_UNSIGNED_SHORT, 0);
    
    glBindVertexArray(0);

    //End the shader program
    glUseProgram(0);

    glutSwapBuffers();
}
