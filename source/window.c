#include <GL/glew.h>
#include <GL/freeglut.h>
#include "window.h"
#include "camera.h"

#define WINDOW_TITLE "Create"

void init_glut(int *argc, char **argv) {
    glutInit(argc, argv);
}

void init_window(int width, int height) {
    glutInitContextVersion(3, 3);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow(WINDOW_TITLE);
    glutReshapeFunc(reshape);
}

void attach_display_func(void (*func)(void)) {
    glutDisplayFunc(func);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    change_aspect(width, height);
}
