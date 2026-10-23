#ifndef JALFREZA
#define JALFREZA

#include "../s21_common.h"

void *s21_memchr(const void *str, int c, s21_size n);
int s21_memcmp(const void *str1, const void *str2, s21_size n);
void *s21_memcpy(void *dest, const void *src, s21_size n);
void *s21_memset(void *str, int c, s21_size n);
char *s21_strncat(char *dest, const char *src, s21_size n);

#endif