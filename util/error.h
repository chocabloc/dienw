#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "opengl.h"

static inline void exit_err() {
    glfwTerminate();
    exit(-1);
}

#define error_if(cond, msg, ...) do {                              \
    if (!(cond)) break;                                            \
    fprintf(stderr, "\x1b[1;31merror:\x1b[0m " msg " \x1b[0;90m("  \
            "%d@%s: %s)\x1b[0m\n"__VA_OPT__(,) __VA_ARGS__,        \
            __LINE__, __FILE__, #cond);                            \
    exit_err();                                                    \
} while(0);

#define test_gl_error() do {                                    \
    int err = glGetError();                                     \
    error_if(err != GL_NO_ERROR, "OpenGL error: %d.", err);     \
} while(0);

char* gl_error_to_str(int err);
