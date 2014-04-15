#ifndef _KSTRING_H
#define _KSTRING_H

#include <stdint.h>

const char *kstring_new(const char*);
const char *kstring_newl(const char*,size_t);
void kstring_destroy(char*);

uint8_t is_kstring(const char*);
size_t kstrlen(const char*);

#endif
