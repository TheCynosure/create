#ifndef SHADERS_H
#define SHADERS_H

#include <GLFW/glfw3.h>

GLuint init_shader(const char* shader_path, GLenum shader_type);
GLuint init_program(GLuint shaders[], int shaders_num);

#endif
