#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#include <stdint.h>

int memcmp(const void*, const void*, size_t size);
void* memcpy(void* __restrict, const void* __restrict, size_t size);
void* memmove(void*, const void*, size_t size);
void* memset(void*, int, size_t size);
size_t strlen(const char*);
void unsigned_to_string(uint64_t value, char *str);
unsigned get_unsigned2string_final_size(uint64_t value);
#endif