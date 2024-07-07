#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

int memcmp(const void*, const void*, size_t size);
void* memcpy(void* __restrict, const void* __restrict, size_t size);
void* memmove(void*, const void*, size_t size);
void* memset(void*, int, size_t size);
size_t strlen(const char*);

#endif