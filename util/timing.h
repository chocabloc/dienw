#pragma once

#include "common.h"

#ifdef IS_UNIX
    #define millisleep(x) usleep(1000*(x))
#elif IS_WINDOWS
    #define millisleep(x) Sleep(x)
#endif