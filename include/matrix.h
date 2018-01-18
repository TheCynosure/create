#pragma once

#include <GL/glew.h>
#include "cst_types.h"

/*
 * This header is for holding commonly used Matrix functions.
 * Examples are constructing and adding to specific matrix elements.
 * All functions operate on the matrices in column major order.
 */


struct Mat4 {
    float m[16];
};

void add_translation(struct Mat4 *mat, struct Vec3 vec);
void set_translation(struct Mat4 *mat, struct Vec3 vec);
void add_scale(struct Mat4 *mat, struct Vec3 vec);
void set_scale(struct Mat4 *mat, struct Vec3 vec);
