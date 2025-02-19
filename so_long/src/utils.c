#include "so_long.h"

void error_exit(const char *msg) {
    printf("Error\n%s\n", msg);
    exit(1);
}