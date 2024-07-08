#pragma once

#include <stddef.h>

#include "util/vmath.h"

typedef int obj_id;

typedef struct {
    bool is_init;
    unsigned int VAO;
} gldata_t;

typedef struct {
    size_t nverts;
    size_t ntris;
    vec3_t* verts;
    int* tris;
    gldata_t gldata;
} mesh_t;
typedef struct {
    mesh_t mesh;
} object_t;

typedef struct {
    obj_id id;
    vec3_t pos;
    mat3_t trans;
} instance_t;

void mgr_init();
object_t* mgr_get_obj(obj_id id);
