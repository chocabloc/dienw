#include <stdlib.h>

#include "util/vmath.h"
#include "util/error.h"
#include "util/opengl.h"

#include "gfx/shader.h"
#include "manager.h"

static int nobjs;
static object_t* objs;

static int nshdrs;
static shader_t* shdrs;

static vec3_t cube_verts[] = {
    -0.5, -0.5, -0.5,
    0.5, -0.5, -0.5,
    0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5,
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
    // just load a few things manually for now

    nobjs = 1;
    objs = calloc(1, sizeof(object_t)*1);
    objs[0].mesh =  (mesh_t) {
        .verts = cube_verts,
        .tris = cube_tris,
        .nverts = 8,
        .ntris = 12
    };
    objs[0].shdr = 0;

    nshdrs = 1;
    shdrs = calloc(1, sizeof(shader_t)*1);
    shdrs[0].prog = shader_make_program("data/shaders/shader.vert",
                                        "data/shaders/shader.frag");
    shdrs[0].uniforms.mat_vm = glGetUniformLocation(shdrs[0].prog, "mat_vm");
    shdrs[0].uniforms.mat_p = glGetUniformLocation(shdrs[0].prog, "mat_p");
}

object_t* mgr_get_object(obj_id id) {
    error_if(id >= nobjs, "no such object: %d.", id);
    return &(objs[id]);
}

shader_t* mgr_get_shader(shdr_id id) {
    error_if(id >= nshdrs, "no such shader: %d.", id);
    return &(shdrs[id]);
}

void mgr_new_instance(obj_id id, instance_t* ins) {
    error_if(id >= nobjs, "no such object: %d.", id);
    ins->id = id;
    ins->trans = (mat4_t) {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}
