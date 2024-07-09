#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "opengl.h"

static inline void exit_err() {
    glfwTerminate();
    exit(-1);
}

#define error_if(cond, msg, ...) do {                        \
    if (!(cond)) break;                                      \
    fprintf(stderr, "\e[1;31merror:\e[0m " msg " \e[0;90m("  \
            "%d@%s: %s)\e[0m\n", __VA_ARGS__                 \
            __VA_OPT__(,)  __LINE__, __FILE__, (#cond));     \
    exit_err();                                              \
} while(0);

#define test_gl_error() do {                                    \
    int err = glGetError();                                     \
    error_if(err != GL_NO_ERROR, "%d.", err);                   \
} while(0);

char* gl_error_to_str(int err);
