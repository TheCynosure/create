#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cglm/cglm.h>
#include "camera.h"
#include "window.h"

float frustum_scale = 0.0f;
vec3 camera_pos;
vec3 camera_rot;
uint32_t old_mouse_pos[] = {320, 240};

float calc_frustum_scale_from_pov(float fov_deg) {
    //Turn the degree argument into radians.
    const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
    float fov_rad = fov_deg * deg_to_rad;
    //Return the cotangent of fov / 2
    return 1.0f / tan(fov_rad / 2.0f);
}

void get_look_at_target(float dir_to_cam[3]) {
    dir_to_cam[0] = camera_pos[0];
    dir_to_cam[1] = camera_pos[1];
    dir_to_cam[2] = camera_pos[2] + TARGET_RAD;
    
    glm_vec_rotate(dir_to_cam, glm_rad(camera_rot[2]), (vec3){0.0f, 0.0f, 1.0f});
    glm_vec_rotate(dir_to_cam, glm_rad(camera_rot[1]), (vec3){0.0f, 1.0f, 0.0f});
    glm_vec_rotate(dir_to_cam, glm_rad(camera_rot[0]), (vec3){1.0f, 0.0f, 0.0f}); 
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

    //Change the original old mouse positions to the new middle of the screen so rotation will not be all screwy.
    old_mouse_pos[0] = 0;
    old_mouse_pos[1] = 0;

    //Also change the rotation back to the original 0, 0, 0
    camera_rot[0] = 0; 
    camera_rot[1] = 0; 
    camera_rot[2] = 0;

    //Set the new perspective matrix in the shader.
    glUseProgram(persp_program);
    glUniformMatrix4fv(perspective_mat_uniform, 1, GL_FALSE, persp_mat);
    glUseProgram(0);
}

void camera_move_callback(int x, int y) {
    
    int32_t delta_x = old_mouse_pos[0] - x;
    int32_t delta_y = old_mouse_pos[1] - y;
    old_mouse_pos[0] = x;
    old_mouse_pos[1] = y;

    //Rotation about the Y-Axis but treat it like the Z for later.
    camera_rot[1] += delta_x * X_ROT_SPEED;
    //Rotation about the X-Axis
    camera_rot[0] += delta_y * Y_ROT_SPEED;
}

void get_world_to_cam_mat(mat4 *mat) {
    vec3 up = {0.0f, 1.0f, 0.0f};
    float look_at_target_pos[3];
    get_look_at_target(look_at_target_pos);
    glm_lookat(camera_pos, look_at_target_pos, up, *mat);
}

void set_world_to_cam_mat(GLuint program_id) {
    GLuint loc = glGetUniformLocation(program_id, "world_to_cam_mat");
    mat4 look_at_mat = GLM_MAT4_IDENTITY_INIT;
    get_world_to_cam_mat(&look_at_mat);
    glUniformMatrix4fv(loc, 1, GL_FALSE, (float*) look_at_mat);
}
