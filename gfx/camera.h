#pragma once

#include "util/vmath.h"

typedef struct {
    // angle of rotation about x and y axes
    // (x is applied first, then y. no z)
    float xrot, yrot;

    // position of origin of camera
    vec3_t pos;

    // camera properties
    // TODO: some sort of aspect ratio needed
    float depth, znear, zfar;

    // view and projection matrices
    mat4_t view, proj;
} camera_t;

// updates view+projection matrix for given camera
void cam_update(camera_t* cam);
