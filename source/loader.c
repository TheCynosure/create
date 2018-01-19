#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "loader.h"

/* Returns an array of data which is the vertex and color data.
 * It is up to the user to free this array when they are finished with it.
 */
float *load_general_format_verts(char* filename, size_t *size) {
    //Open the file and check for errors.
    FILE* vert_file = fopen(filename, "r");
    if(vert_file == NULL)
        return NULL;

    char line[1024];

    //Get the number of lines in the file.
    size_t lines = 0;
    while(fgets(line, 1024, vert_file) != NULL) { lines++; }
    fseek(vert_file, 0, SEEK_SET);

    //Read line by line the input file.
    *size = lines * 4 * sizeof(float);
    float *data = malloc(*size);
    int i = 0;
    while(fgets(line, 1024, vert_file) != NULL) {
        //Extract the four floats on each line.
        sscanf(line, "%ff, %ff, %ff, %ff", &data[i], &data[i+1], &data[i+2], &data[i+3]);
        i += 4;
    }

    return data;
}
