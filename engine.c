#include "util/opengl.h"
#include "util/timing.h"
//#include "util/error.h"

#include "gfx/gfx.h"
#include "gfx/shader.h"

int main(void) {
    gfx_init();
    mgr_init();

    instance_t cube;
    mgr_new_instance(0, &cube);

    // main loop
    while(!gfx_should_close()) {
        //glBindVertexArray(VAO);
        gfx_clear();
        gfx_draw_object(&cube);
        //test_gl_error();
        gfx_render();

        // TODO: time better
        millisleep(16);
    }

    gfx_close();
    return 0;
}
