#ifndef MINTVM_STDC_H
#define MINTVM_STDC_H

// TODO: replace with the standard library's own headers once the project has them.

extern "C" {

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(list, last) ((void)last, __builtin_va_info(&list))
#define va_end(list) ((void)0)

int printf(const char* format, ...);
int vprintf(const char* format, va_list args);
int strcmp(const char* a, const char* b);
char* strcpy(char* dst, const char* src);
char* strcat(char* dst, const char* src);
unsigned long strlen(const char* s);
void* memcpy(void* dst, const void* src, unsigned long size);
void* memset(void* dst, int value, unsigned long size);

}

#endif
