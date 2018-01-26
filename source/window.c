#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdint.h>
#include "window.h"
#include "camera.h"

#define WINDOW_TITLE "Create"

static uint16_t window_width = 0;
static uint16_t window_height = 0;

void init_glut(int *argc, char **argv) {
    glutInit(argc, argv);
}

void init_window(uint16_t width, uint16_t height) {
    glutInitContextVersion(3, 3);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow(WINDOW_TITLE);
    glutReshapeFunc(reshape);

    window_width = width;
    window_height = height;
}

void attach_display_func(void (*func)(void)) {
    glutDisplayFunc(func);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    change_aspect(width, height);

    window_width = width;
    window_height = height;
}

void get_height_and_width(uint16_t *width, uint16_t *height) {
    *width = window_width;
    *height = window_height;
}
