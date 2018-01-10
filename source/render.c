#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include "render.h"

typedef struct {
    GLuint vertex_vbo;
    GLuint vertex_vao;
} Obj;

const float vertex_pos[] = {
	 0.25f,  0.25f, 0.75f, 1.0f,
	 0.25f, -0.25f, 0.75f, 1.0f,
	-0.25f,  0.25f, 0.75f, 1.0f,

	 0.25f, -0.25f, 0.75f, 1.0f,
	-0.25f, -0.25f, 0.75f, 1.0f,
	-0.25f,  0.25f, 0.75f, 1.0f,

	 0.25f,  0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,
	 0.25f, -0.25f, -0.75f, 1.0f,

	 0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,

	-0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f, -0.25f,  0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,

	-0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,

	 0.25f,  0.25f,  0.75f, 1.0f,
	 0.25f, -0.25f, -0.75f, 1.0f,
	 0.25f, -0.25f,  0.75f, 1.0f,

	 0.25f,  0.25f,  0.75f, 1.0f,
	 0.25f,  0.25f, -0.75f, 1.0f,
	 0.25f, -0.25f, -0.75f, 1.0f,

	 0.25f,  0.25f, -0.75f, 1.0f,
	 0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f,  0.25f,  0.75f, 1.0f,

	 0.25f,  0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,

	 0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f,  0.75f, 1.0f,
	 0.25f, -0.25f,  0.75f, 1.0f,

	 0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f,  0.75f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

};

Obj simple_obj;
GLuint shader_program;
GLuint offset_uniform;

void render_init(GLuint programID) {
    shader_program = programID;

    //Generate a vertex buffer based on our vertex_pos array
    glGenBuffers(1, &simple_obj.vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, simple_obj.vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_pos), vertex_pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //Generate a vao.
    glGenVertexArrays(1, &simple_obj.vertex_vao);
    glBindVertexArray(simple_obj.vertex_vao);

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

    //Setup the uniforms and buffers
    glUniform2f(offset_uniform, 0.5f, 0.5f);
    glBindBuffer(GL_ARRAY_BUFFER, simple_obj.vertex_vbo);
    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); //Color
   
    //Set the pointers to the 2 shader inputs.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertex_pos) / 2));

    //Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //Disable the shader inputs
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    //End the shader program
    glUseProgram(0);

    //Ask for this function to be called again.
    glutPostRedisplay();
}
