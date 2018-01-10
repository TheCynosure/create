#include <GL/glew.h>
#include <GL/freeglut.h>
#include "window.h"

#define WINDOW_TITLE "Create"

void init_glut(int *argc, char **argv) {
    glutInit(argc, argv);
}

void init_window(int width, int height) {
    glutInitContextVersion(3, 3);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow(WINDOW_TITLE);
}

void attach_display_func(void (*func)(void)) {
    glutDisplayFunc(func);
}
