#include <stdlib.h>

#include "util/vmath.h"
#include "util/error.h"

#include "manager.h"

static size_t nobjs;
static object_t* objs;

static vec3_t cube_verts[] = (vec3_t[]) {
    -0.5, -0.4, 0.0,
    0.5, -0.5, 0.0,
    0.5, 0.5, 0.0,
    -0.5, 0.5, 0.0,
    -0.5, -0.5, 0.5,
    0.5, -0.5, 0.5,
    0.5, 0.5, 0.5,
    -0.5, 0.5, 0.5
};

static int cube_tris[] = {
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    3, 2, 6,
    3, 6, 7,

    0, 1, 5,
    0, 5, 4,

    1, 5, 6,
    1, 6, 2,

    0, 4, 7,
    0, 7, 3
};

void mgr_init() {
    // TODO: find a way to load assets from disk
    // just a cube for now

    nobjs = 1;
    objs = calloc(1, sizeof(object_t)*1);
    objs[0].mesh =  (mesh_t) {
        .verts = cube_verts,
        .tris = cube_tris,
        .nverts = 8,
        .ntris = 12
    };
}

object_t* mgr_get_obj(obj_id id) {
    error_if(id >= nobjs, "no such object: %d.", id);
    return &(objs[id]);
}
