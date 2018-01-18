#pragma once

#include <stdbool.h>

/*
 * This Header holds basic functions for loading commonly used data from files.
 * All functions that are given a double pointer as an argument except the end
 * user to free the data at the end of his/her program.
 */

bool load_general_format_verts(float data[], char* filename);
