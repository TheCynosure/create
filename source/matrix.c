#include <GL/glew.h>
#include <string.h>
#include "cst_types.h"
#include "matrix.h"

void add_translation(struct Mat4 *mat, struct Vec3 vec) {
    mat->m[12] += vec.x;
    mat->m[13] += vec.y;
    mat->m[14] += vec.z;
}

void set_translation(struct Mat4 *mat, struct Vec3 vec) {
    mat->m[12] = vec.x;
    mat->m[13] = vec.y;
    mat->m[14] = vec.z;
}

void add_scale(struct Mat4 *mat, struct Vec3 vec) {
    mat->m[0] += vec.x;
    mat->m[5] += vec.y;
    mat->m[10] += vec.z;
}

void set_scale(struct Mat4 *mat, struct Vec3 vec) {
    mat->m[0] = vec.x;
    mat->m[5] = vec.y;
    mat->m[10] = vec.z;
}
