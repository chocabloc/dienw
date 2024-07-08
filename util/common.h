#pragma once

// basic includes
#include <stdbool.h>

// cross-platform stuff
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #define IS_UNIX
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32) 
    #define IS_WINDOWS
    #include <windows.h>
#endif
