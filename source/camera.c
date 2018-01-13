#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include "camera.h"

void init_camera(GLuint program) {
    GLuint perspective_mat_uniform = glGetUniformLocation(program, "perspective_mat");
    persp_program = program;

    memset(persp_mat, 0, sizeof(float) * 16);
    persp_mat[0] = FRUSTUM_SCALE;
    persp_mat[5] = FRUSTUM_SCALE;
    persp_mat[10] = (Z_FAR + Z_NEAR) / (Z_NEAR - Z_FAR);
    persp_mat[14] = (2 * Z_FAR * Z_NEAR) / (Z_NEAR - Z_FAR);
    persp_mat[11] = -1.0f;

    glUseProgram(program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}

void change_aspect(int w, int h) {
    GLuint perspective_mat_uniform = glGetUniformLocation(persp_program, "perspective_mat");

    persp_mat[0] = FRUSTUM_SCALE / (w / (float) h);
    glUseProgram(persp_program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}

