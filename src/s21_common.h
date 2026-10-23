#ifndef S21_COMMON_H
#define S21_COMMON_H

#if defined(_WIN64) || defined(__x86_64__) || defined(__LP64__)
typedef unsigned long long s21_size;
#else
typedef unsigned int s21_size;
#endif

#ifndef S21_NULL
#define S21_NULL ((void *)0)
#endif

#ifndef EPERM
#define EPERM 1
#endif
#ifndef ENOENT
#define ENOENT 2
#endif
#ifndef ESRCH
#define ESRCH 3
#endif
#ifndef EINTR
#define EINTR 4
#endif
#ifndef EIO
#define EIO 5
#endif
#ifndef ENXIO
#define ENXIO 6
#endif
#ifndef E2BIG
#define E2BIG 7
#endif
#ifndef ENOEXEC
#define ENOEXEC 8
#endif
#ifndef EBADF
#define EBADF 9
#endif
#ifndef ECHILD
#define ECHILD 10
#endif
#ifndef ENOMEM
#define ENOMEM 12
#endif
#ifndef EACCES
#define EACCES 13
#endif
#ifndef EFAULT
#define EFAULT 14
#endif
#ifndef ENOTBLK
#define ENOTBLK 15
#endif
#ifndef EBUSY
#define EBUSY 16
#endif
#ifndef EEXIST
#define EEXIST 17
#endif
#ifndef EXDEV
#define EXDEV 18
#endif
#ifndef ENODEV
#define ENODEV 19
#endif
#ifndef ENOTDIR
#define ENOTDIR 20
#endif
#ifndef EISDIR
#define EISDIR 21
#endif
#ifndef EINVAL
#define EINVAL 22
#endif
#ifndef ENFILE
#define ENFILE 23
#endif
#ifndef EMFILE
#define EMFILE 24
#endif
#ifndef ENOTTY
#define ENOTTY 25
#endif
#ifndef ETXTBSY
#define ETXTBSY 26
#endif
#ifndef EFBIG
#define EFBIG 27
#endif
#ifndef ENOSPC
#define ENOSPC 28
#endif
#ifndef ESPIPE
#define ESPIPE 29
#endif
#ifndef EROFS
#define EROFS 30
#endif
#ifndef EMLINK
#define EMLINK 31
#endif
#ifndef EPIPE
#define EPIPE 32
#endif
#ifndef EDOM
#define EDOM 33
#endif
#ifndef ERANGE
#define ERANGE 34
#endif

#ifndef EAGAIN
#ifdef __APPLE__
#define EAGAIN 35
#else
#define EAGAIN 11
#endif
#endif

#ifndef EDEADLK
#ifdef __APPLE__
#define EDEADLK 11
#else
#define EDEADLK 35
#endif
#endif

typedef struct {
  int flag_minus, flag_plus, flag_space;

  int width;
  int precision;
  char length;
  char specifier;
} FormatParams;

#endif