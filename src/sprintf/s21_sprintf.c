#include "s21_sprintf.h"

#include <stdarg.h>

static char *s21_itoa(unsigned int num, char *buf, int is_unsigned) {
  if (num == 0) {
    buf[0] = '0';
    buf[1] = '\0';
  } else {
    int is_negative = 0;
    if ((int)num < 0 && !is_unsigned) {
      is_negative = 1;
      buf[0] = '-';
      num = -(int)num;
    }

    int len_num = 0;
    for (unsigned int i = num; i > 0; i /= 10) len_num++;

    int sign_shift = is_negative + len_num;
    for (int i = 0; i < len_num; i++) {
      buf[sign_shift - 1 - i] = (num % 10) + '0';
      num /= 10;
    }

    buf[sign_shift] = '\0';
  }

  return buf;
}

static char *s21_append_string(char *new_str, char *old_str) {
  while (*new_str != '\0') {
    *old_str = *new_str;
    old_str++;
    new_str++;
  }
  return old_str;
}

static const char *s21_parse_flags(const char *format, FormatParams *params) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    switch (*format) {
      case '-':
        params->flag_minus = 1;
        break;
      case '+':
        params->flag_plus = 1;
        break;
      case ' ':
        params->flag_space = 1;
        break;
    }

    format++;
  }
  return format;
}

static const char *s21_parse_width(const char *format, FormatParams *params) {
  int num = 0;
  while (*format >= '0' && *format <= '9') {
    num = num * 10 + (*format - '0');
    format++;
  }
  params->width = num;
  return format;
}

static const char *s21_parse_precision(const char *format,
                                       FormatParams *params) {
  if (*format == '.') {
    format++;
    int num = 0;
    while (*format >= '0' && *format <= '9') {
      num = num * 10 + (*format - '0');
      format++;
    }
    params->precision = num;
  }

  return format;
}

static const char *s21_parse_length(const char *format, FormatParams *params) {
  if (*format == 'h' || *format == 'l') {
    params->length = *format;
    format++;
  }
  return format;
}

static char *s21_apply_width(char *str, const char *buf, int len,
                             const FormatParams *params) {
  if (params->width > len && params->flag_minus == 0) {
    for (int i = 0; i < params->width - len; i++) {
      *str = ' ';
      str++;
    }
    for (int i = 0; i < len; i++) {
      *str = buf[i];
      str++;
    }
  } else if (params->width > len && params->flag_minus == 1) {
    for (int i = 0; i < len; i++) {
      *str = buf[i];
      str++;
    }
    for (int i = 0; i < params->width - len; i++) {
      *str = ' ';
      str++;
    }
  } else {
    for (int i = 0; i < len; i++) {
      *str = buf[i];
      str++;
    }
  }
  return str;
}

static char *s21_specifier_c(char *str, va_list args,
                             const FormatParams *params) {
  char c = (char)va_arg(args, int);
  char buf[2];
  buf[0] = c;
  buf[1] = '\0';

  int len = 1;

  return s21_apply_width(str, buf, len, params);
}

static char *s21_specifier_d(char *str, va_list args,
                             const FormatParams *params) {
  int num;
  if (params->length == 'l') {
    num = va_arg(args, int);
  } else if (params->length == 'h') {
    num = (short)va_arg(args, int);
  } else {
    num = va_arg(args, int);
  }
  char buf[20];
  int pre = 0;

  if (params->flag_plus == 1 && num >= 0) {
    buf[0] = '+';
    pre = 1;
    s21_itoa(num, buf + 1, 0);
  } else if (params->flag_space == 1 && num >= 0) {
    buf[0] = ' ';
    pre = 1;
    s21_itoa(num, buf + 1, 0);
  } else {
    s21_itoa(num, buf, 0);
    if (buf[0] == '-') {
      pre = 1;
    }
  }

  int len = 0;
  while (buf[len] != '\0') len++;

  if (params->precision >= 0) {
    int zero = params->precision - (len - pre);
    if (zero > 0) {
      for (int i = len; i >= pre; i--) {
        buf[i + zero] = buf[i];
      }
      for (int i = 0; i < zero; i++) {
        buf[pre + i] = '0';
      }
      len += zero;
    }
  }

  return s21_apply_width(str, buf, len, params);
}

static char *change_mv(char *move, char str) {
  *move = str;
  move++;
  return move;
}

static char *s21_specifier_f(char *str, va_list args,
                             const FormatParams *params) {
  double num = va_arg(args, double);
  char buf[40];
  char *move = buf;
  int prec = (params->precision >= 0) ? params->precision : 6;

  if (num < 0) {
    move = change_mv(move, '-');
    num = -num;
  } else if (params->flag_plus == 1) {
    move = change_mv(move, '+');
  } else if (params->flag_space == 1) {
    move = change_mv(move, ' ');
  }

  double mult = 1.0;
  for (int i = 0; i < prec; i++) mult *= 10.0;

  int int_part = (int)num;
  double frac = num - int_part;
  frac = frac * mult + 0.5;
  int frac_part = (int)frac;

  if (frac_part == (int)mult) {
    int_part++;
    frac_part = 0;
  }

  char buf1[20];
  s21_itoa(int_part, buf1, 0);
  move = s21_append_string(buf1, move);

  if (prec > 0) {
    move = change_mv(move, '.');

    char buf2[20];
    s21_itoa(frac_part, buf2, 0);

    int len2 = 0;
    while (buf2[len2] != '\0') len2++;
    for (int i = 0; i < prec - len2; i++) {
      move = change_mv(move, '0');
    }
    move = s21_append_string(buf2, move);
  }

  int len = move - buf;
  return s21_apply_width(str, buf, len, params);
}

static char *s21_specifier_s(char *str, va_list args,
                             const FormatParams *params) {
  const char *s = va_arg(args, char *);

  if (s == S21_NULL) {
    s = "(null)";
  }

  int len = 0;
  while (s[len] != '\0') len++;

  if (params->precision >= 0 && params->precision < len) {
    len = params->precision;
  }

  return s21_apply_width(str, s, len, params);
}

static char *s21_specifier_u(char *str, va_list args,
                             const FormatParams *params) {
  unsigned long num;
  if (params->length == 'l') {
    num = va_arg(args, unsigned long);
  } else if (params->length == 'h') {
    num = (unsigned short)va_arg(args, int);
  } else {
    num = va_arg(args, int);
  }

  char buf[20];
  s21_itoa(num, buf, 1);

  int len = 0;
  while (buf[len] != '\0') len++;

  if (params->precision >= 0) {
    int zero = params->precision - len;
    if (zero > 0) {
      for (int i = len; i >= 0; i--) {
        buf[i + zero] = buf[i];
      }
      for (int i = 0; i < zero; i++) {
        buf[i] = '0';
      }
      len += zero;
    }
  }
  return s21_apply_width(str, buf, len, params);
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  const char *str_start = str;

  while (*format != '\0') {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;
    } else {
      FormatParams params = {0};
      params.precision = -1;

      format++;
      format = s21_parse_flags(format, &params);
      format = s21_parse_width(format, &params);
      format = s21_parse_precision(format, &params);
      format = s21_parse_length(format, &params);

      params.specifier = *format;
      if (*format != '\0') format++;

      switch (params.specifier) {
        case 'c':
          str = s21_specifier_c(str, args, &params);
          break;
        case 'd':
          str = s21_specifier_d(str, args, &params);
          break;
        case 'f':
          str = s21_specifier_f(str, args, &params);
          break;
        case 's':
          str = s21_specifier_s(str, args, &params);
          break;
        case 'u':
          str = s21_specifier_u(str, args, &params);
          break;
        case '%':
          *str++ = '%';
          break;
      }
    }
  }

  *str = '\0';
  va_end(args);

  return str - str_start;
}