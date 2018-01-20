#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "shaders.h"
#include "camera.h"
#include "window.h"
#include "render.h"

#define WIDTH 640
#define HEIGHT 480

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* user_param)
{
    if(type == GL_DEBUG_TYPE_ERROR)
        fprintf(stderr, "Callback:\nType: %x\nSeverity: %x\nMessage: %s\n", type, severity, message);
}

int main(int argc, char** argv) {
    //Initialize Glut Window
    init_glut(&argc, argv);
    init_window(WIDTH, HEIGHT);

    //Set the main function to be called each render loop.
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

    //Enable error callbacks in OpenGL
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC) MessageCallback, NULL);

    glViewport(0, 0, (GLsizei) WIDTH, (GLsizei) HEIGHT);

    //Compile the shaders and link the shader program
    GLuint shader_list[2];
    shader_list[0] = init_shader("shaders/vertshader.txt", GL_VERTEX_SHADER);
    shader_list[1] = init_shader("shaders/fragshader.txt", GL_FRAGMENT_SHADER);
    GLuint program = init_program(shader_list, 2);

    init_camera(program, WIDTH, HEIGHT);

    //Setup the input handling.
    glutPassiveMotionFunc(camera_move_callback);

    //Setup the renderer and enter the main rendering loop.
    render_init(program);
    glutMainLoop();

    return 0;
}
