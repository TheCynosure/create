#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cglm/cglm.h>
#include "camera.h"

float frustum_scale = 0.0f;
vec3 camera_pos;
vec3 camera_rot;
vec3 old_camera_pos;

float calc_frustum_scale_from_pov(float fov_deg) {
    //Turn the degree argument into radians.
    const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
    float fov_rad = fov_deg * deg_to_rad;
    //Return the cotangent of fov / 2
    return 1.0f / tan(fov_rad / 2.0f);
}

void get_look_at_target(float *dir_to_cam) {
    //See here for explanation:
    // http://opengl.datenwolf.net/gltut/html/Positioning/Tutorial%2007.html
    float deg_to_rad = M_PI / 180.0;
    //Convert the rotation of the camera to radians.
    float phi = camera_rot[0] * deg_to_rad;
    float theta = camera_rot[1] * deg_to_rad;

    float sin_theta = sinf(theta);
    float cos_theta = cosf(theta);
    float sin_phi = sinf(phi);
    float cos_phi = cosf(phi);

    dir_to_cam[0] = sin_theta * cos_phi * TARGET_RAD + camera_pos[0];
    dir_to_cam[1] = cos_theta * TARGET_RAD + camera_pos[1];
    dir_to_cam[2] = sin_theta * sin_phi * TARGET_RAD + camera_pos[2];
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

void camera_move_callback(int x, int y) {
    int delta_x = x - old_camera_pos[0];
    int delta_y = y - old_camera_pos[1];
    old_camera_pos[0] = x;
    old_camera_pos[1] = y;

    camera_rot[0] += delta_x * ROT_SPEED;
    camera_rot[1] += delta_y * ROT_SPEED;
}

void get_camera_to_world_mat(mat4 *mat) {
    vec3 up = {0.0f, 1.0f, 0.0f};
    float look_at_target_pos[3];
    get_look_at_target(&look_at_target_pos);
    glm_lookat(camera_pos, look_at_target_pos, up, *mat);
}

void set_camera_to_world_mat(GLuint program_id) {
    GLuint loc = glGetUniformLocation(program_id, "cam_to_world_mat");
    mat4 look_at_mat = GLM_MAT4_IDENTITY_INIT;
    get_camera_to_world_mat(&look_at_mat);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (float*) look_at_mat);
}
