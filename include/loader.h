#ifndef LOADER_H
#define LOADER_H

/* Loads a simple 4 float vertex format file.
 * Vertexs are presented each on a new line in the following format.
 * v1f, v2f, v3f, v4f.
 * Color data is in the same format following the vertex data.
 * Vertices are put in the data array and then color data.
 * Returns a non-zero number on error.
 */
int load_general_verts(float data[], char* filename);

#endif

