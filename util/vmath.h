#pragma once

typedef struct {
    union {
        struct {
            float x, y, z;
        };
        float dat[3];
    };
} vec3_t;

typedef vec3_t mat3_t[3];
