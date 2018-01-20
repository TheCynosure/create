#pragma once

#include <GL/glew.h>
#include <stdint.h>
#include <cglm/cglm.h>

#define CAMERA_Z_NEAR 0.5f
#define CAMERA_Z_FAR 1000.0f
#define TARGET_RAD 100.0f
#define ROT_SPEED 0.001f

GLuint persp_program;
float persp_mat[16];

void get_look_at_target(float *vec);
void init_camera(GLuint program, uint16_t w, uint16_t h);
void change_aspect(uint16_t w, uint16_t h);
void camera_move_callback(int x, int y);
void get_camera_to_world_mat(mat4 *mat);
void set_camera_to_world_mat(GLuint program_id);
