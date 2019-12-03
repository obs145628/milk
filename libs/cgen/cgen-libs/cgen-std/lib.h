#ifndef CGEN_STD_LIB_H_
#define CGEN_STD_LIB_H_

#include <stddef.h>
#include <stdint.h>

void* cgen_std_malloc(size_t size);
void cgen_std_free(void* ptr);
void cgen_std_print_str(char* s);
void cgen_std_print_int(int64_t x);
void* cgen_std_memcpy(void* dst, void* src, size_t count);
void* cgen_std_memmove(void* dst, void* src, size_t count);
void cgen_std_exit(int exit_code);

#endif //!CGEN_STD_LIB_H_