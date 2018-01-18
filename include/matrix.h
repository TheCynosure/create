#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>

/* All Operations are done in Column Major Order, for reference:
 * 0 | 4 | 8 | 12
 * ------------
 * 1 | 5 | 9 | 13
 * ------------
 * 2 | 6 | 10| 14
 * ------------
 * 3 | 7 | 11| 15
 */


typedef struct { float m[16]; } Mat4;

void set_to_identity(Mat4 *mat);
void add_translation(Mat4 *mat, float x, float y, float z);
void set_translation(Mat4 *mat, float x, float y, float z);
void add_scale(Mat4 *mat, float x, float y, float z);
void set_scale(Mat4 *mat, float x, float y, float z);
#endif
