#ifndef _KSTRING_H
#define _KSTRING_H

#include <stdlib.h>
#include <stdint.h>

const char *kstring_new(const char*);
const char *kstring_newl(const char*,size_t);
void kstring_destroy(const char*);

uint8_t is_kstring(const char*);
size_t kstrlen(const char*);
const char *kstrcat(const char *, const char *);

#endif
