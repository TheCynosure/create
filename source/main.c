#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "shaders.h"
#include "camera.h"
#include "window.h"
#include "render.h"

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
        const GLchar* message, const void* user_param) {
    if(type == GL_DEBUG_TYPE_ERROR)
        fprintf(stderr, "Callback:\nType: %x\nSeverity: %x\nMessage: %s\n", type, severity, message);
}

int main(int argc, char** argv) { 
    //Initialize Glut Window
    init_glut(&argc, argv);
    init_window(640, 480);
    //Main Render function in render.c
    attach_display_func(render_main);

    //Initialize Glew
    glewExperimental = GL_TRUE;
    glewInit();
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        fprintf(stderr, "Glew_Init Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    
    //Print Glew Version
    fprintf(stdout, "Using GLEW: %s\n", glewGetString(GLEW_VERSION));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC) MessageCallback, NULL);

    //Default viewport setup.
    glViewport(0, 0, (GLsizei) 640, (GLsizei) 480);

    //Compile the shaders and link the shader program
    GLuint shader_list[2];
    shader_list[0] = init_shader("shaders/vertshader.txt", GL_VERTEX_SHADER);
    shader_list[1] = init_shader("shaders/fragshader.txt", GL_FRAGMENT_SHADER);
    GLuint program = init_program(shader_list, 2);

    //Initialize Camera and other Uniforms
    init_camera(program);
    
    render_init(program);
    glutMainLoop();

    return 0;
}
