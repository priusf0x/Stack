#include "tools.h"

#include "stdlib.h"
#include "string.h"

void* recalloc(void*  pointer,
               size_t current_size,
               size_t new_size)
{
    pointer = realloc(pointer, new_size);
    memset((char*) pointer + current_size, 0, new_size - current_size);

    return pointer;
}
