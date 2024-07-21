#include <math.h>
#include "util/vmath.h"
//#include "util/error.h"

#include "gfx/gfx.h"
#include "gfx/camera.h"

int main(void) {
    gfx_init();
    mgr_init();

    instance_t cube;
    mgr_new_instance(0, &cube);

    camera_t cam = {
        .xrot = 0.0,
        .yrot = 0.0,
        .depth = 1.0,
        .pos = (vec3_t) {0, 0, 2.0},
        .znear = 0.1, .zfar = 100.0
    };

    // main loop
    float t = 0;
    while(!gfx_should_close()) {
        gfx_clear();
        cube.trans.dat[0].x = (float)sin(t);
        cube.trans.dat[0].z = (float)cos(t);
        cube.trans.dat[2].x = (float)cos(t);
        cube.trans.dat[2].z = -(float)sin(t);
        cam.pos.y = sin(t);
        cam.xrot = -0.5*sin(t);
        gfx_draw_object(&cam, &cube);

        //test_gl_error();
        gfx_render();

        // TODO: time better
        //millisleep(16);
        t += 0.01;
    }

    gfx_close();
    return 0;
}
