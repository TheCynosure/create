#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shaders.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void window_resize_callback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}

const float vertex_pos[] = {
     0.0f, 0.5f, 0.0f, 1.0f,
     0.5f, -0.366f, 0.0f, 1.0f,
    -0.5f, -0.366f, 0.0f, 1.0f,
     1.0f,    0.0f, 0.0f, 1.0f,
     0.0f,    1.0f, 0.0f, 1.0f,
     0.0f,    0.0f, 1.0f, 1.0f,
};

int main(int argc, char** argv) {

    fprintf(stdout, "Using GLEW: %s\n", glewGetString(GLEW_VERSION));

    GLFWwindow *window;
    if(!glfwInit())
        return -1;

    glfwSetErrorCallback(error_callback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(1920, 1080, "create", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, window_resize_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
     
    glewInit();
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
   
    glViewport(0, 0, (GLsizei) 1920, (GLsizei) 1080);

    GLuint shader_list[2];
    shader_list[0] = init_shader("shaders/vertshader.txt", GL_VERTEX_SHADER);
    shader_list[1] = init_shader("shaders/fragshader.txt", GL_FRAGMENT_SHADER);

    GLuint program = init_program(shader_list, 2);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_pos), vertex_pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        // 48 =  4 (Byte size of float) * 4 (Number of Floats in Vec4) * 3 (Number of Vertices)
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
