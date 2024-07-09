#pragma once

typedef struct {
    union {
        struct {
            float x, y, z;
        };
        float dat[3];
    };
} vec3_t;

typedef struct {
    vec3_t dat[3];
} mat3_t;
