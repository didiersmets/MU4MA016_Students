#include <stdbool.h>
#include <stddef.h> // for size_t

struct Triangle {
    // Indices of the vertices that form the triangle. 
    size_t v1;
    size_t v2;
    size_t v3;
};