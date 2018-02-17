#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cglm/cglm.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "render.h"
#include "camera.h"
#include "loader.h"
#include "basic_obj.h"

#define NUM_OF_VERT 36

static float *vertex_pos;
static GLshort element_array[] = {
	0, 2, 1,
	3, 2, 0,
	4, 5, 6,
	6, 7, 4,
	8, 9, 10,
	11, 13, 12,
	14, 16, 15,
	17, 16, 14,
};

struct Basic_Obj wedge_1;
GLuint shader_program;
float offset = 0.0f;

void render_init(GLuint program_id) {
    shader_program = program_id;

    //Load up the vertex data
    size_t vertex_size;
    vertex_pos = load_general_format_verts("data/wedge.verts", &vertex_size);

    //Generate a vertex buffer based on our vertex_pos array
    add_vertices(&wedge_1, vertex_pos, vertex_size);

    //Generate a Element buffer
    add_indices(&wedge_1, element_array, sizeof(element_array) / sizeof(element_array[0]));

    size_t color_data_offset = NUM_OF_VERT * 4 * sizeof(float);
    add_vao(&wedge_1, color_data_offset);

    //Set the scale to be a default of 1.
    wedge_1.scale[0] = 1.0f;
    wedge_1.scale[1] = 1.0f;
    wedge_1.scale[2] = 1.0f;

    //Enable Culling of back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    //Enable the Depth Buffer and Testing method
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDepthRange(0.0f, 1.0f);

    atexit(render_cleanup);
    free(vertex_pos);
}

void render_main(void) {
    offset += 0.01;

    //Clear the Screen
    glClearColor(fabs(sin(offset)), fabs(cos(offset)), fabs(tan(offset)), 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Turn on the Shaders
    glUseProgram(shader_program);

    set_world_to_cam_mat(shader_program);

    wedge_1.offset[2] = -5.0f;
    wedge_1.rotation[2] = cos(offset) * M_PI;
    wedge_1.scale[0] = fabs(sin(offset));
    draw_obj(&wedge_1, shader_program);

    //End the shader program
    glUseProgram(0);

    glutSwapBuffers();
}

void render_cleanup(void) {
    cleanup_obj(&wedge_1);
}
