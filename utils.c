
#include <string.h>
#include "utils.h"

void zero_memory(void *ptr, size_t size) {
    memset(ptr, 0, size);
}
