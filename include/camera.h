#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#define Z_NEAR 0.5f
#define Z_FAR 1000.0f

GLuint persp_program;
float persp_mat[16];

void init_camera(GLuint program, int w, int h);
void change_aspect(int w, int h);

#endif

