#ifndef WINDOW_H
#define WINDOW_H

#define FREEGLUT_PRINT_ERRORS
#define FREEGLUT_PRINT_WARNINGS

#include <stdint.h>

void init_glut(int *argc, char **argv);
void init_window(uint16_t width, uint16_t height);
void reshape(int width, int height);
void attach_display_func(void (*func)(void));
void get_height_and_width(uint16_t *width, uint16_t *height);

#endif
