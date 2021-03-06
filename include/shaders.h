#pragma once

#include <GL/glew.h>
#include <stddef.h>

GLuint init_shader(const char* shader_path, GLenum shader_type);
GLuint init_program(GLuint shaders[], size_t shaders_num);
