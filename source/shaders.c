#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shaders.h"

/* Attempts to load a file into a text buffer.
 * Will return null if runs into an exception loading the 
 * file.
 */
const char* load_file_into_buffer(const char* file_path) {
    int fd = open(file_path, O_RDONLY);
    if(fd < 0)
        return NULL;
    //Find the size of the file.
    struct stat stat_struct;
    if(fstat(fd, &stat_struct) < 0)
        return NULL;

    char* buff = malloc(stat_struct.st_size + 1);
    read(fd, buff, stat_struct.st_size);
    *(buff + stat_struct.st_size) = '\0';
    close(fd);
    return buff;
}

GLuint init_shader(const char* shader_path, GLenum shader_type) {
    const char* shader_buffer = load_file_into_buffer(shader_path);
    if(shader_buffer == NULL)
        return 0;

    //Compile the Shader
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_buffer, NULL);
    glCompileShader(shader);

    //Check for Compilation Errors
    GLint stat;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
    if(stat == GL_FALSE) {
        //If there was an error then print it.
        GLint info_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

        GLchar info_log[info_len + 1];
        glGetShaderInfoLog(shader, info_len, NULL, info_log);

        fprintf(stderr, "Shader Compile Error!\nPath: %s\nError: %s\n", shader_path, info_log);
    }

    free((char*)shader_buffer);
    return shader;
}

GLuint init_program(GLuint shaders[], int shaders_num) {
    GLuint program = glCreateProgram();

    for(int i = 0; i < shaders_num; i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(program);

    GLint stat;
    glGetProgramiv(program, GL_LINK_STATUS, &stat);
    if(stat == GL_FALSE) {
        GLint info_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
        
        GLchar info_log[info_len + 1];
        glGetProgramInfoLog(program, info_len, NULL, info_log);
        fprintf(stderr, "Shader Program Linking Failure!\nError:%s\n", info_log);
    }

    for(int i = 0; i < shaders_num; i++)
        glDetachShader(program, shaders[i]);

    return program;
}
