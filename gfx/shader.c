#include <stdio.h>
#include <stdlib.h>

#include "util/opengl.h"
#include "util/error.h"

#include "shader.h"

static char log[512];

static GLuint compile(const char* path, GLenum type) {
    // open the file and get size
    FILE* f = fopen(path, "r");
    error_if(f == NULL, "couldn't open file %s.", path);
    fseek(f, 0, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    // read them in
    char* src = calloc(1, fsize + 1);
    fread(src, fsize, 1, f);

    // try to compile
    int success;
    GLuint sh = glCreateShader(type);
    glShaderSource(sh, 1, (const char**)&src, NULL);
    glCompileShader(sh);

    // check if succeeded
    glGetShaderiv(sh, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(sh, 512, NULL, log);
        fprintf(stderr, "\nIn file %s:\n%s", path, log);
        error_if(!success, "shader compilation failed.");
    }

    // clean up
    fclose(f);
    free(src);

    return sh;
}

int shader_make_program(const char* vsh_path, const char* fsh_path) {
    GLuint vsh = compile(vsh_path, GL_VERTEX_SHADER),
           fsh = compile(fsh_path, GL_FRAGMENT_SHADER);

    // create and link program
    GLuint program = glCreateProgram();
    glAttachShader(program, fsh);
    glAttachShader(program, vsh);
    glLinkProgram(program);

    // check if succeeded
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, log);
        fprintf(stderr, "\nIn files %s and %s:\n%s", vsh_path, fsh_path, log);
        error_if(!success, "shader linkage failed.");
    }

    // clean up
    glDeleteShader(vsh);
    glDeleteShader(fsh);

    return program;
}
