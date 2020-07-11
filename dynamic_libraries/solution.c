#include <stddef.h>
#include "solution.h"

int stringStat(const char *string, size_t multiplier, int *count) {
    size_t len = 0;
    for (len = 0; string[len] != '\0'; ++len);
    len *= multiplier;
    ++*count;
    return len;
}
