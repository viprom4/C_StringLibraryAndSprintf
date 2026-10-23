#include "jalfreza.h"

void *s21_memchr(const void *str, int c, s21_size n) {
  const unsigned char *bytes = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  void *res = S21_NULL;

  int found = 0;
  for (s21_size i = 0; i < n && !found; i++) {
    if (ch == bytes[i]) {
      res = (void *)&bytes[i];
      found = 1;
    }
  }

  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size n) {
  const unsigned char *bytes1 = (const unsigned char *)str1;
  const unsigned char *bytes2 = (const unsigned char *)str2;
  int byte_difference = 0;

  for (s21_size i = 0; i < n && byte_difference == 0; i++) {
    byte_difference = (int)(bytes1[i] - bytes2[i]);
  }

  return byte_difference;
}

void *s21_memcpy(void *dest, const void *src, s21_size n) {
  unsigned char *dest_ptr = (unsigned char *)dest;
  const unsigned char *src_ptr = (const unsigned char *)src;

  for (s21_size i = 0; i < n; i++) {
    dest_ptr[i] = src_ptr[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size n) {
  unsigned char *str_ptr = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;

  for (s21_size i = 0; i < n; i++) {
    str_ptr[i] = ch;
  }

  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size n) {
  s21_size dest_len = 0;

  while (dest[dest_len] != '\0') dest_len++;

  s21_size i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    dest[dest_len + i] = src[i];
  }

  dest[dest_len + i] = '\0';

  return dest;
}