#pragma once

#include <stdio.h>

typedef struct {
    union {
        struct {
            float x, y, z;
        };
        float dat[3];
    };
} vec3_t;

typedef struct {
    union {
        struct {
            float x, y, z, w;
        };
        float dat[4];
    };
} vec4_t;

typedef struct {
    vec3_t dat[3];
} mat3_t;

typedef struct {
    vec4_t dat[4];
} mat4_t;

// find a*b and store in ab
static inline void matmul4(const mat4_t* a, const mat4_t* b, mat4_t* ab) {
    *ab = (mat4_t) {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                ab->dat[i].dat[k] += a->dat[i].dat[j]*b->dat[j].dat[k];
}

// replace a with transpose of a
static inline void mattrans4(mat4_t* a) {
    for (int i = 0; i < 4; i++)
        for (int j = i+1; j < 4; j++) {
            float tmp = a->dat[i].dat[j];
            a->dat[i].dat[j] = a->dat[j].dat[i];
            a->dat[j].dat[i] = tmp;
        }
}

static inline void printmat(const mat4_t* m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.4f ", m->dat[i].dat[j]);
        }
        printf("\n");
    }
    printf("\n");
}
