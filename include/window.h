#ifndef WINDOW_H
#define WINDOW_H

#define FREEGLUT_PRINT_ERRORS
#define FREEGLUT_PRINT_WARNINGS

void init_glut(int *argc, char **argv);
void init_window(int width, int height);
void attach_display_func(void (*func)(void));
void reshape(int width, int height);

#endif
