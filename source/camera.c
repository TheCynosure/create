#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "camera.h"

float frustum_scale = 0.0f;

float calc_frustum_scale_from_pov(float fov_deg) {
    const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
    float fov_rad = fov_deg * deg_to_rad;
    return 1.0f / tan(fov_rad / 2.0f);
}

void init_camera(GLuint program, int w, int h) {
    GLuint perspective_mat_uniform = glGetUniformLocation(program, "perspective_mat");
    persp_program = program;

    frustum_scale = calc_frustum_scale_from_pov(45.0f);

    memset(persp_mat, 0, sizeof(float) * 16);
    persp_mat[0] = frustum_scale / (w / (float) h);
    persp_mat[5] = frustum_scale;
    persp_mat[10] = (Z_FAR + Z_NEAR) / (Z_NEAR - Z_FAR);
    persp_mat[14] = (2 * Z_FAR * Z_NEAR) / (Z_NEAR - Z_FAR);
    persp_mat[11] = -1.0f;

    glUseProgram(program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}

void change_aspect(int w, int h) {
    GLuint perspective_mat_uniform = glGetUniformLocation(persp_program, "perspective_mat");

    persp_mat[0] = frustum_scale / (w / (float) h);
    glUseProgram(persp_program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}

