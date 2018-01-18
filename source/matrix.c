#include <GL/glew.h>
#include <string.h>
#include "matrix.h"

void set_to_identity(mat4 *mat) {
    memset(mat, 0, sizeof(mat4));
    mat->m[0] = 1.0f;
    mat->m[5] = 1.0f;
    mat->m[10] = 1.0f;
    mat->m[15] = 1.0f;
}

void add_translation(mat4 *mat, float x, float y, float z) {
    mat->m[12] += x;
    mat->m[13] += y;
    mat->m[14] += z;
}

void set_translation(mat4 *mat, float x, float y, float z) {
    mat->m[12] = x;
    mat->m[13] = y;
    mat->m[14] = z; 
}

void add_scale(mat4 *mat, float x, float y, float z) {
    mat->m[0] += x;
    mat->m[5] += y;
    mat->m[10] += z;
}

void set_scale(mat4 *mat, float x, float y, float z) {
    mat->m[0] = x;
    mat->m[5] = y;
    mat->m[10] = z;
}

