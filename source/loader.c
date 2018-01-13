#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

int load_general_verts(float data[], char* filename) {
    //Continually load the float lines into the array.
    FILE* vert_file = fopen(filename, "r");
    if(vert_file == NULL)
        return 1;
    char* line = NULL;
    size_t size;
    int i = 0;
    while(getline(&line, &size, vert_file) > 0) {
        sscanf(line, "%ff, %ff, %ff, %ff", &data[i], &data[i+1], &data[i+2], &data[i+3]);
        i += 4;
    }
    free(line);
    return 0;
}
