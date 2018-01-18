#pragma once

#include <GL/glew.h>
#include <stdint.h>

#define CAMERA_Z_NEAR 0.5f
#define CAMERA_Z_FAR 1000.0f

GLuint persp_program;
float persp_mat[16];

void init_camera(GLuint program, uint16_t w, uint16_t h);
void change_aspect(uint16_t w, uint16_t h);
