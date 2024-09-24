#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    size_t n = (size_t) atoi(argv[1]);
    return 0;
}
