#pragma once

#include <stddef.h>

#include "util/vmath.h"
#include "util/opengl.h"

// for Shaders
typedef int shdr_id;
typedef struct {
    GLuint prog;
    struct {
        GLuint mat_vm;
        GLuint mat_p;
    } uniforms;
} shader_t;

// for 3D objects
typedef int obj_id;
typedef struct {
    size_t nverts;
    size_t ntris;
    vec3_t* verts;
    int* tris;
    GLuint gl_vao;
} mesh_t;
typedef struct {
    mesh_t mesh;
    shdr_id shdr;
    // more stuff to be added here
} object_t;
typedef struct {
    obj_id id;
    mat4_t trans;
} instance_t;

void mgr_init();

object_t* mgr_get_object(obj_id id);
void mgr_new_instance(obj_id id, instance_t* ins);

shader_t* mgr_get_shader(shdr_id id);
