#ifndef STD_CSTRING_H
#define STD_CSTRING_H

// TODO: replace with the standard library's own header once the project has it.

extern "C" {

unsigned long strlen(const char* str);
int strcmp(const char* a, const char* b);
int strncmp(const char* a, const char* b, unsigned long count);
void* memcpy(void* dest, const void* src, unsigned long count);
void* memset(void* dest, int value, unsigned long count);

}

#endif
