#pragma once

/*
 * This Header holds basic functions for loading commonly used data from files.
 * All functions that are given a double pointer as an argument except the end
 * user to free the data at the end of his/her program.
 */

float *load_general_format_verts(char* filename);
