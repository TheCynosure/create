#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "loader.h"

bool load_general_format_verts(float data[], char* filename) {
    //Open the file and check for errors.
    FILE* vert_file = fopen(filename, "r");
    if(vert_file == NULL)
        return false;

    //Read line by line the input file.
    char line[1024];
    int i = 0;
    while(fgets(line, 1024, vert_file) != NULL) {
        //Extract the four floats on each line.
        sscanf(line, "%ff, %ff, %ff, %ff", &data[i], &data[i+1], &data[i+2], &data[i+3]);
        i += 4;
    }

    return true;
}
