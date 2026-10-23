#ifndef DOTTEDLU
#define DOTTEDLU

#include "../s21_common.h"

char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size n);
char *s21_strncpy(char *dest, const char *src, s21_size n);
s21_size s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);

#endif