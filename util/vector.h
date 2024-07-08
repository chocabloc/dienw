#include "stdlib.h"

#define vec_struct(type)   \
    struct {               \
        size_t len;        \
        size_t alloc_size; \
        type* data;        \
    }

#define vec_new(type, name) vec_struct(type) name = { 0 }

#define vec_new_static(type, name) static vec_new(type, name)

// change the size of a vector, increasing allocation if needed
#define vec_resize(vec, newsize)                                           \
    {                                                                      \
        (vec)->len = newsize;                                              \
        if ((vec)->alloc_size < (vec)->len * sizeof(*((vec)->data))) {     \
            (vec)->alloc_size = ((vec)->len * sizeof(*((vec)->data))) * 2; \
            (vec)->data = realloc((vec)->data, (vec)->alloc_size);         \
        }                                                                  \
    }

// adds a new element to the back of a vector
#define vec_push_back(vec, elem)            \
    {                                       \
        vec_resize(vec, (vec)->len + 1);    \
        (vec)->data[(vec)->len - 1] = elem; \
    }

// gets element at specified index of vector
#define vec_at(vec, index) (vec)->data[index]

// removes element at specified index, repacking it
#define vec_erase(vec, index)                                    \
    {                                                            \
        memcpy(&((vec)->data[index + 1]), &((vec)->data[index]), \
            sizeof((vec)->data[0]) * (vec)->len - index - 1);    \
        (vec)->len--;                                            \
    }

// erases element with specified value, repacking it
#define vec_erase_val(vec, val)                         \
    {                                                   \
        for (size_t __i = 0; __i < (vec)->len; __i++) { \
            if (vec_at(vec, __i) == (val)) {            \
                vec_erase(vec, __i);                    \
                break;                                  \
            }                                           \
        }                                               \
    }

// initialize a vector
#define vec_init(v)       \
    {                     \
        v.len = 0;        \
        v.alloc_size = 0; \
        v.data = NULL;    \
    }
