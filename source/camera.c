#include <GL/glew.h>
#include <stdio.h>
#include "camera.h"

void init_camera(GLuint program) {
    GLuint frustum_scale_uniform = glGetUniformLocation(program, "frustum_scale");
    GLuint z_near_uniform = glGetUniformLocation(program, "z_near");
    GLuint z_far_uniform = glGetUniformLocation(program, "z_far");
    
    glUseProgram(program);
    glUniform1f(frustum_scale_uniform, 1.0f);
    glUniform1f(z_near_uniform, 1.0f);
    glUniform1f(z_far_uniform, 3.0f);
    glUseProgram(0);
}
