#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "camera.h"

float frustum_scale = 0.0f;

float calc_frustum_scale_from_pov(float fov_deg) {
    //Turn the degree argument into radians.
    const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
    float fov_rad = fov_deg * deg_to_rad;
    //Return the cotangent of fov / 2
    return 1.0f / tan(fov_rad / 2.0f);
}

void init_camera(GLuint program, uint16_t w, uint16_t h) {
    //Get the location of the perspective matrix.
    persp_program = program;
    GLuint perspective_mat_uniform = glGetUniformLocation(program, "perspective_mat");

    //Calculate the frustum scale.
    frustum_scale = calc_frustum_scale_from_pov(45.0f);

    //Setup the perspective matrix.
    memset(persp_mat, 0, sizeof(float) * 16);
    persp_mat[0] = frustum_scale / (w / (float) h);
    persp_mat[5] = frustum_scale;
    persp_mat[10] = (CAMERA_Z_FAR + CAMERA_Z_NEAR) / (CAMERA_Z_NEAR - CAMERA_Z_FAR);
    persp_mat[14] = (2 * CAMERA_Z_FAR * CAMERA_Z_NEAR) / (CAMERA_Z_NEAR - CAMERA_Z_FAR);
    persp_mat[11] = -1.0f;

    //Set the perspective matrix in the shader.
    glUseProgram(program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}

void change_aspect(uint16_t w, uint16_t h) {
    //Get the location of the perspective matrix.
    GLuint perspective_mat_uniform = glGetUniformLocation(persp_program, "perspective_mat");

    //Change the x frustum_scale depending on the aspect ratio.
    persp_mat[0] = frustum_scale / (w / (float) h);

    //Set the new perspective matrix in the shader.
    glUseProgram(persp_program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}
