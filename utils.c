
#include <stdio.h>
#include "utils.h"

void print_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}

void print_success(const char *message) {
    printf("Success: %s\n", message);
}
