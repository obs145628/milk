#include "lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* cgen_std_malloc(size_t size)
{
    return malloc(size);
}

void cgen_std_free(void* ptr)
{
    free(ptr);
}

void cgen_std_print_str(char* s)
{
    printf("%s", s);
}

void cgen_std_print_int(int64_t x)
{
    printf("%ld", (long) x);
}

void* cgen_std_memcpy(void* dst, void* src, size_t count)
{
    return memcpy(dst, src, count);
}

void* cgen_std_memmove(void* dst, void* src, size_t count)
{
    return memmove(dst, src, count);
}

void cgen_std_exit(int exit_code)
{
    exit(exit_code);
}