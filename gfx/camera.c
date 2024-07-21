#include <math.h>
#include "camera.h"
#include "util/vmath.h"

void cam_update(camera_t* cam) {
    float   srx = sinf(-cam->xrot), crx = cosf(-cam->xrot),
            sry = sinf(-cam->yrot), cry = cosf(-cam->yrot);

    // calculate the view matrix
    auto mrot = (mat4_t) {
        cry,    -srx*sry,   -crx*sry,   0,
        0,      crx,        -srx,       0,
        sry,    srx*cry,    crx*cry,    0,
        0,      0,          0,          1
    };
    auto mtrans = (mat4_t) {
        1, 0, 0, -cam->pos.x,
        0, 1, 0, -cam->pos.y,
        0, 0, 1, -cam->pos.z,
        0, 0, 0, 1
    };
    matmul4(&mrot, &mtrans, &(cam->view));
    //printmat(&(cam->view));
    //exit(-1);

    // and then the projection matrix
    float   dinv = 1/cam->depth,
            a = dinv*(cam->zfar/(cam->znear - cam->zfar)),
            b = dinv*((cam->znear*cam->zfar)/(cam->znear - cam->zfar));
    cam->proj = (mat4_t) {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, a, b,
        0, 0, -dinv, 0
    };
}
