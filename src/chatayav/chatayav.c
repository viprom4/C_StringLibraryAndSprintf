#include "chatayav.h"

s21_size s21_strlen(const char *str) {
  s21_size length = 0;

  while (str[length] != '\0') length++;

  return length;
}

static int s21_is_in_string(char c, const char *str) {
  int result = 0;
  int i = 0;

  while (str[i] != '\0' && result == 0) {
    if (str[i] == c) {
      result = 1;
    }

    i++;
  }

  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int i = 0;

  while (str1[i] != '\0' && result == S21_NULL) {
    if (s21_is_in_string(str1[i], str2)) {
      result = (char *)&str1[i];
    }

    i++;
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  int i = 0;

  while (str[i] != '\0') {
    if (str[i] == (char)c) {
      result = (char *)&str[i];
    }

    i++;
  }

  if ((char)c == '\0') {
    result = (char *)&str[i];
  }

  return result;
}

static int s21_strings_equal(const char *str1, const char *str2) {
  int equal = 1;
  int i = 0;

  while (str2[i] != '\0' && equal == 1) {
    if (str1[i] != str2[i]) {
      equal = 0;
    }

    i++;
  }

  return equal;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int i = 0;

  if (needle[0] == '\0') {
    result = (char *)haystack;
  }

  while (haystack[i] != '\0' && result == S21_NULL) {
    if (s21_strings_equal(&haystack[i], needle)) {
      result = (char *)&haystack[i];
    }

    i++;
  }

  return result;
}

static int s21_is_delimiter(char c, const char *delim) {
  int result = 0;
  int i = 0;

  while (delim[i] != '\0' && result == 0) {
    if (c == delim[i]) {
      result = 1;
    }

    i++;
  }

  return result;
}

static char *s21_skip_delimiters(char *str, const char *delim) {
  char *result = str;

  while (*result != '\0' && s21_is_delimiter(*result, delim)) {
    result++;
  }

  return result;
}

static char *s21_find_token_end(char *str, const char *delim) {
  char *result = str;

  while (*result != '\0' && !s21_is_delimiter(*result, delim)) {
    result++;
  }

  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *current = S21_NULL;

  char *token = S21_NULL;
  char *end = S21_NULL;

  if (str != S21_NULL) {
    current = str;
  }

  if (current != S21_NULL) {
    current = s21_skip_delimiters(current, delim);
  }

  if (current != S21_NULL && *current != '\0') {
    token = current;
    end = s21_find_token_end(current, delim);

    if (*end != '\0') {
      *end = '\0';
      current = end + 1;
    } else {
      current = S21_NULL;
    }
  }

  return token;
}