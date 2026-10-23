#include "dottedlu.h"

#include "../sprintf/s21_sprintf.h"

#ifdef __APPLE__

const char *error_messages[] = {[0] = "Success",
                                [EPERM] = "Operation not permitted",
                                [ENOENT] = "No such file or directory",
                                [ESRCH] = "No such process",
                                [EINTR] = "Interrupted system call",
                                [EIO] = "Input/output error",
                                [ENXIO] = "Device not configured",
                                [E2BIG] = "Argument list too long",
                                [ENOEXEC] = "Exec format error",
                                [EBADF] = "Bad file descriptor",
                                [ECHILD] = "No child processes",
                                [EDEADLK] = "Resource deadlock avoided",
                                [ENOMEM] = "Cannot allocate memory",
                                [EACCES] = "Permission denied",
                                [EFAULT] = "Bad address",
                                [ENOTBLK] = "Block device required",
                                [EBUSY] = "Device or resource busy",
                                [EEXIST] = "File exists",
                                [EXDEV] = "Cross-device link",
                                [ENODEV] = "Operation not supported by device",
                                [ENOTDIR] = "Not a directory",
                                [EISDIR] = "Is a directory",
                                [EINVAL] = "Invalid argument",
                                [ENFILE] = "Too many open files in system",
                                [EMFILE] = "Too many open files",
                                [ENOTTY] = "Inappropriate ioctl for device",
                                [ETXTBSY] = "Text file busy",
                                [EFBIG] = "File too large",
                                [ENOSPC] = "No space left on device",
                                [ESPIPE] = "Illegal seek",
                                [EROFS] = "Read-only file system",
                                [EMLINK] = "Too many links",
                                [EPIPE] = "Broken pipe",
                                [EDOM] = "Numerical argument out of domain",
                                [ERANGE] = "Result too large",
                                [EAGAIN] = "Resource temporarily unavailable"};

#else

const char *error_messages[] = {[0] = "Success",
                                [EPERM] = "Operation not permitted",
                                [ENOENT] = "No such file or directory",
                                [ESRCH] = "No such process",
                                [EINTR] = "Interrupted system call",
                                [EIO] = "Input/output error",
                                [ENXIO] = "Device not configured",
                                [E2BIG] = "Argument list too long",
                                [ENOEXEC] = "Exec format error",
                                [EBADF] = "Bad file descriptor",
                                [ECHILD] = "No child processes",
                                [EAGAIN] = "Resource temporarily unavailable",
                                [ENOMEM] = "Cannot allocate memory",
                                [EACCES] = "Permission denied",
                                [EFAULT] = "Bad address",
                                [ENOTBLK] = "Block device required",
                                [EBUSY] = "Device or resource busy",
                                [EEXIST] = "File exists",
                                [EXDEV] = "Cross-device link",
                                [ENODEV] = "Operation not supported by device",
                                [ENOTDIR] = "Not a directory",
                                [EISDIR] = "Is a directory",
                                [EINVAL] = "Invalid argument",
                                [ENFILE] = "Too many open files in system",
                                [EMFILE] = "Too many open files",
                                [ENOTTY] = "Inappropriate ioctl for device",
                                [ETXTBSY] = "Text file busy",
                                [EFBIG] = "File too large",
                                [ENOSPC] = "No space left on device",
                                [ESPIPE] = "Illegal seek",
                                [EROFS] = "Read-only file system",
                                [EMLINK] = "Too many links",
                                [EPIPE] = "Broken pipe",
                                [EDOM] = "Numerical argument out of domain",
                                [ERANGE] = "Result too large",
                                [EDEADLK] = "Resource deadlock avoided"};

#endif

#define ERROR_COUNT (sizeof(error_messages) / sizeof(error_messages[0]))

char *s21_strchr(const char *str, int c) {
  unsigned char chr = (unsigned char)c;
  int pos = 0;
  int stop = 0;
  char *result = S21_NULL;
  while ((unsigned char)str[pos] != '\0' && stop != 1) {
    if ((unsigned char)str[pos] == chr) {
      result = (char *)&str[pos];
      stop = 1;
    }
    pos++;
  }
  if (chr == '\0') {
    if ((unsigned char)str[pos] == '\0') {
      result = (char *)&str[pos];
    }
  }
  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size n) {
  int result = 0;
  int stop = 0;

  for (s21_size i = 0; i < n && result == 0 && stop == 0; i++) {
    unsigned char c1 = (unsigned char)str1[i];
    unsigned char c2 = (unsigned char)str2[i];

    if (c1 == '\0' || c2 == '\0') {
      stop = 1;
    }

    if (c1 != c2) {
      result = c1 - c2;
    }
  }

  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size n) {
  char *orig = dest;
  int stop = 0;

  for (s21_size i = 0; i < n; i++) {
    if (!stop) {
      unsigned char c = (unsigned char)src[i];
      dest[i] = c;
      if (c == '\0') {
        stop = 1;
      }
    } else {
      dest[i] = '\0';
    }
  }

  return orig;
}

s21_size s21_strcspn(const char *str1, const char *str2) {
  s21_size result = 0;
  int stop = 0;

  for (s21_size i = 0; str1[i] != '\0' && stop == 0; i++) {
    int found = 0;
    for (s21_size j = 0; str2[j] != '\0'; j++) {
      if ((unsigned char)str1[i] == (unsigned char)str2[j]) {
        found = 1;
      }
    }

    if (found) {
      stop = 1;
    } else {
      result += 1;
    }
  }

  return result;
}

char *s21_strerror(int errnum) {
  static char buffer[256];
  char *result;

  if (errnum >= 0 && (s21_size)errnum < ERROR_COUNT &&
      error_messages[errnum] != S21_NULL) {
    result = (char *)error_messages[errnum];
  } else {
    s21_sprintf(buffer, "Unknown error %d", errnum);
    result = buffer;
  }

  return result;
}