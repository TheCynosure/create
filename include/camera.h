#pragma once

#include <GL/glew.h>
#include <stdint.h>
#include <cglm/cglm.h>

#define CAMERA_Z_NEAR 0.5f
#define CAMERA_Z_FAR 1000.0f
#define TARGET_RAD -100.0f
#define X_ROT_SPEED 0.5f
#define Y_ROT_SPEED 0.5f

GLuint persp_program;
float persp_mat[16];

void get_look_at_target(float *vec);
void init_camera(GLuint program, uint16_t w, uint16_t h);
void change_aspect(uint16_t w, uint16_t h);
void camera_move_callback(int x, int y);
void get_world_to_cam_mat(mat4 *mat);
void set_world_to_cam_mat(GLuint program_id);
