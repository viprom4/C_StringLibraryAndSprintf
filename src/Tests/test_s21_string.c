#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memchr_found_begin) {
  char str[] = "Hello";
  ck_assert_ptr_eq(s21_memchr(str, 'H', 5), memchr(str, 'H', 5));
}
END_TEST

START_TEST(test_memchr_found_middle) {
  char str[] = "Hello World";
  ck_assert_ptr_eq(s21_memchr(str, 'W', 11), memchr(str, 'W', 11));
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = "Hello";
  ck_assert_ptr_eq(s21_memchr(str, 'z', 5), memchr(str, 'z', 5));
}
END_TEST

START_TEST(test_memchr_zero_n) {
  char str[] = "Hello";
  ck_assert_ptr_eq(s21_memchr(str, 'H', 0), memchr(str, 'H', 0));
}
END_TEST

START_TEST(test_memchr_null_char) {
  char str[] = "Hel\0lo";
  ck_assert_ptr_eq(s21_memchr(str, '\0', 6), memchr(str, '\0', 6));
}
END_TEST

START_TEST(test_memchr_unsigned_char) {
  unsigned char str[] = {0x01, 0x02, 0xFF, 0x03, 0x04};
  ck_assert_ptr_eq(s21_memchr(str, 0xFF, 5), memchr(str, 0xFF, 5));
  ck_assert_ptr_eq(s21_memchr(str, (unsigned char)-1, 5),
                   memchr(str, (unsigned char)-1, 5));
}
END_TEST

START_TEST(test_memcmp_equal) {
  const char str[] = "Hello";
  ck_assert_int_eq(s21_memcmp(str, str, 5), 0);
}
END_TEST

START_TEST(test_memcmp_greater) {
  const char s1[] = "Hello", s2[] = "Hella";
  ck_assert(s21_memcmp(s1, s2, 5) > 0);
}
END_TEST

START_TEST(test_memcmp_less) {
  const char s1[] = "Hella", s2[] = "Hello";
  ck_assert(s21_memcmp(s1, s2, 5) < 0);
}
END_TEST

START_TEST(test_memcmp_zero_n) {
  const char s1[] = "Hello", s2[] = "World";
  ck_assert_int_eq(s21_memcmp(s1, s2, 0), memcmp(s1, s2, 0));
}
END_TEST

START_TEST(test_memcmp_unsigned) {
  const unsigned char s1[] = {0x01, 0x80, 0x02};
  const unsigned char s2[] = {0x01, 0x7F, 0x02};
  ck_assert_int_eq(s21_memcmp(s1, s2, 3), memcmp(s1, s2, 3));
}
END_TEST

START_TEST(test_memcpy_normal) {
  const char src[] = "Hello World";
  char dest1[20] = {0};
  char dest2[20] = {0};

  void *res1 = s21_memcpy(dest1, src, 12);
  memcpy(dest2, src, 12);

  ck_assert_ptr_eq(res1, dest1);
  ck_assert_str_eq(dest1, dest2);
  ck_assert_mem_eq(dest1, dest2, 12);
}
END_TEST

START_TEST(test_memcpy_with_null) {
  const char src[] = "Hel\0lo";
  char dest1[10] = {0};
  char dest2[10] = {0};

  void *res1 = s21_memcpy(dest1, src, 6);
  memcpy(dest2, src, 6);

  ck_assert_ptr_eq(res1, dest1);
  ck_assert_str_eq(dest1, dest2);
  ck_assert_mem_eq(dest1, dest2, 6);
}
END_TEST

START_TEST(test_memcpy_zero_n) {
  const char src[] = "Hello";
  char dest1[10] = "World";
  char dest2[10] = "World";

  void *res1 = s21_memcpy(dest1, src, 0);
  memcpy(dest2, src, 0);

  ck_assert_ptr_eq(res1, dest1);
  ck_assert_str_eq(dest1, dest2);
  ck_assert_mem_eq(dest1, dest2, 6);
}
END_TEST

START_TEST(test_memset_normal) {
  char str1[20] = "Hello World";
  char str2[20] = "Hello World";

  void *res1 = s21_memset(str1, 'X', 11);
  memset(str2, 'X', 11);

  ck_assert_ptr_eq(res1, str1);
  ck_assert_str_eq(str1, str2);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_memset_zero_n) {
  char str1[20] = "Hello World";
  char str2[20] = "Hello World";

  size_t n = 0;

  void *res1 = s21_memset(str1, 'X', n);
  memset(str2, 'X', n);

  ck_assert_ptr_eq(res1, str1);
  ck_assert_str_eq(str1, str2);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_memset_partial) {
  char str1[20] = "Hello World";
  char str2[20] = "Hello World";

  void *res1 = s21_memset(str1, 'A', 5);
  memset(str2, 'A', 5);

  ck_assert_ptr_eq(res1, str1);
  ck_assert_str_eq(str1, str2);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_memset_with_null) {
  char str1[20] = "Hello World";
  char str2[20] = "Hello World";

  void *res1 = s21_memset(str1, 0, 5);
  memset(str2, 0, 5);

  ck_assert_ptr_eq(res1, str1);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_memset_negative) {
  char str1[20] = "Hello World";
  char str2[20] = "Hello World";

  void *res1 = s21_memset(str1, -1, 5);
  memset(str2, -1, 5);

  ck_assert_ptr_eq(res1, str1);
  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_strncat_normal) {
  char dest1[30] = "Hello", dest2[30] = "Hello";
  const char src[] = " World";
  ck_assert_ptr_eq(s21_strncat(dest1, src, 6), dest1);
  strncat(dest2, src, 6);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_partial) {
  char dest1[30] = "Hello", dest2[30] = "Hello";
  const char src[] = " World";
  s21_strncat(dest1, src, 3);
  strncat(dest2, src, 3);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_zero_n) {
  char dest1[30] = "Hello", dest2[30] = "Hello";
  const char src[] = " World";
  s21_strncat(dest1, src, 0);
  strncat(dest2, src, 0);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char dest1[30] = "", dest2[30] = "";
  const char src[] = "Hello";
  s21_strncat(dest1, src, 5);
  strncat(dest2, src, 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr__first_occurrence) {
  const char *str = "hello world";
  const char *expected = strchr(str, 'l');
  const char *got = s21_strchr(str, 'l');

  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_end) {
  const char *str = "abc";
  const char *expected = strchr(str, 'c');
  const char *got = s21_strchr(str, 'c');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_not_found) {
  const char *str = "abc";
  const char *expected = strchr(str, 'd');
  const char *got = s21_strchr(str, 'd');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_null_terminator) {
  const char *str = "abc";
  const char *expected = strchr(str, '\0');
  const char *got = s21_strchr(str, '\0');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_empty_string) {
  const char *str = "";
  const char *expected = strchr(str, 'a');
  const char *got = s21_strchr(str, 'a');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_empty_string_null) {
  const char *str = "";
  const char *expected = strchr(str, '\0');
  const char *got = s21_strchr(str, '\0');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_multiple_occurrences) {
  const char *str = "abracadabra";
  const char *expected = strchr(str, 'a');
  const char *got = s21_strchr(str, 'a');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_special_characters) {
  const char *str = "hello\tworld\n";
  const char *expected = strchr(str, '\t');
  const char *got = s21_strchr(str, '\t');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_case_sensitive) {
  const char *str = "Hello";
  const char *expected = strchr(str, 'h');
  const char *got = s21_strchr(str, 'h');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strchr_control_char) {
  const char *str =
      "abc\x01"
      "def";
  const char *expected = strchr(str, '\x01');
  const char *got = s21_strchr(str, '\x01');
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_equal_full) {
  const char *s1 = "hello";
  const char *s2 = "hello";
  s21_size n = 10;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_equal_within_n) {
  const char *s1 = "abcde";
  const char *s2 = "abcXY";
  s21_size n = 3;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_greater) {
  const char *s1 = "hello";
  const char *s2 = "hella";
  s21_size n = 5;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_gt(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_less) {
  const char *s1 = "abc";
  const char *s2 = "abd";
  s21_size n = 3;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_lt(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_difference_after_n) {
  const char *s1 = "abcd";
  const char *s2 = "abce";
  s21_size n = 3;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_prefix_n_greater) {
  const char *s1 = "abc";
  const char *s2 = "abcde";
  s21_size n = 5;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_lt(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_zero_n) {
  const char *s1 = "abc";
  const char *s2 = "xyz";
  s21_size n = 0;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_empty_vs_nonempty) {
  const char *s1 = "";
  const char *s2 = "abc";
  s21_size n = 3;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_lt(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_both_empty) {
  const char *s1 = "";
  const char *s2 = "";
  s21_size n = 5;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_case_sensitive) {
  const char *s1 = "Hello";
  const char *s2 = "hello";
  s21_size n = 5;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_ne(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_unsigned_char) {
  const char *s1 = "abc\x80";
  const char *s2 = "abc\x81";
  s21_size n = 4;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_lt(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_with_null_in_middle) {
  const char *s1 = "ab\0cd";
  const char *s2 = "ab\0ef";
  s21_size n = 5;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncmp_control_char) {
  const char *s1 = "abc\x01";
  const char *s2 = "abc\x02";
  s21_size n = 4;
  int expected = strncmp(s1, s2, n);
  int got = s21_strncmp(s1, s2, n);
  ck_assert_int_lt(got, 0);
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(test_strncpy_src_longer_than_n) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  const char *src = "hello world";
  s21_size n = 5;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  ck_assert_str_eq(dest1, dest2);
  ck_assert_int_eq(dest2[5], '\0');
}
END_TEST

START_TEST(test_strncpy_src_shorter_than_n) {
  char dest1[20] = "xxxxxxxxx";
  char dest2[20] = "xxxxxxxxx";
  const char *src = "abc";
  s21_size n = 6;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  ck_assert_str_eq(dest1, dest2);
  for (s21_size i = 0; i < n; i++) {
    ck_assert_int_eq(dest1[i], dest2[i]);
  }
}
END_TEST

START_TEST(test_strncpy_equal_length) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  const char *src = "abc";
  s21_size n = 3;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_zero_n) {
  char dest1[20] = "hello";
  char dest2[20] = "hello";
  const char *src = "world";
  s21_size n = 0;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_empty_src) {
  char dest1[10] = "abcde";
  char dest2[10] = "abcde";
  const char *src = "";
  s21_size n = 5;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  for (s21_size i = 0; i < n; i++) {
    ck_assert_int_eq(dest1[i], dest2[i]);
  }
}
END_TEST

START_TEST(test_strncpy_unsigned_char) {
  char dest1[10] = {0};
  char dest2[10] = {0};
  const char *src = "abc\x81\x82";
  s21_size n = 5;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  for (s21_size i = 0; i < n; i++) {
    ck_assert_int_eq((unsigned char)dest1[i], (unsigned char)dest2[i]);
  }
}
END_TEST

START_TEST(test_strncpy_with_null_in_src) {
  char dest1[20] = {0};
  char dest2[20] = {0};
  const char *src = "ab\0cd";
  s21_size n = 6;
  strncpy(dest1, src, n);
  char *got = s21_strncpy(dest2, src, n);
  ck_assert_ptr_eq(got, dest2);
  for (s21_size i = 0; i < n; i++) {
    ck_assert_int_eq((unsigned char)dest1[i], (unsigned char)dest2[i]);
  }
}
END_TEST

START_TEST(test_strcspn_no_match) {
  const char *str1 = "abcde";
  const char *str2 = "xyz";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strcspn_match_at_begin) {
  const char *str1 = "abcde";
  const char *str2 = "abx";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strcspn_match_middle) {
  const char *str1 = "hello world";
  const char *str2 = "wo";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strcspn_empty_reject) {
  const char *str1 = "abcde";
  const char *str2 = "";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strcspn_empty_str) {
  const char *str1 = "";
  const char *str2 = "abc";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strcspn_control_chars) {
  const char *str1 =
      "abc\x01"
      "def";
  const char *str2 = "\x01";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strcspn_case_sensitive) {
  const char *str1 = "Hello";
  const char *str2 = "h";
  s21_size expected = strcspn(str1, str2);
  s21_size got = s21_strcspn(str1, str2);
  ck_assert_uint_eq(got, expected);
}
END_TEST

START_TEST(test_strerror_zero) {
  int err = 0;
  const char *expected = strerror(err);
  const char *got = s21_strerror(err);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_strerror_positive) {
  int err = 5;
  const char *expected = strerror(err);
  const char *got = s21_strerror(err);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_strerror_unknown) {
  int err = 9999;
  const char *expected = strerror(err);
  const char *got = s21_strerror(err);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_strerror_negative) {
  int err = -4;
  const char *expected = strerror(err);
  const char *got = s21_strerror(err);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_strlen_normal) {
  const char *str = "Hello World";

  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_empty) {
  const char *str = "";

  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_one_char) {
  const char *str = "A";

  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_spaces) {
  const char *str = "Hello World Test";

  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_special_chars) {
  const char *str = "Hello\tWorld\n";

  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strpbrk_found_begin) {
  const char *str1 = "Hello";
  const char *str2 = "H";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_found_middle) {
  const char *str1 = "Hello World";
  const char *str2 = "W";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_found_from_many) {
  const char *str1 = "Hello World";
  const char *str2 = "aeiou";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  const char *str1 = "Hello";
  const char *str2 = "xyz";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_empty_str2) {
  const char *str1 = "abc";
  const char *str2 = "";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strrchr_first_occurrence) {
  const char *str = "hello world";

  ck_assert_ptr_eq(s21_strrchr(str, 'h'), strrchr(str, 'h'));
}
END_TEST

START_TEST(test_strrchr_last_occurrence) {
  const char *str = "hello world";

  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char *str = "hello";

  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_strrchr_null_terminator) {
  const char *str = "hello";

  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strrchr_empty) {
  const char *str = "";

  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
}
END_TEST

START_TEST(test_strrchr_empty_null) {
  const char *str = "";

  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strstr_begin) {
  const char *haystack = "Hello World";
  const char *needle = "Hello";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_middle) {
  const char *haystack = "Hello World";
  const char *needle = "World";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_end) {
  const char *haystack = "Hello World";
  const char *needle = "ld";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char *haystack = "Hello World";
  const char *needle = "abc";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char *haystack = "Hello World";
  const char *needle = "";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "abc";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_equal) {
  const char *haystack = "Hello";
  const char *needle = "Hello";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strtok_first_token) {
  char str1[] = "Hello World Test";
  char str2[] = "Hello World Test";

  char *expected = strtok(str1, " ");
  char *got = s21_strtok(str2, " ");

  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_strtok_all_tokens) {
  char str1[] = "Hello World Test";
  char str2[] = "Hello World Test";

  char *expected = strtok(str1, " ");
  char *got = s21_strtok(str2, " ");

  while (expected != S21_NULL && got != S21_NULL) {
    ck_assert_str_eq(got, expected);

    expected = strtok(S21_NULL, " ");
    got = s21_strtok(S21_NULL, " ");
  }

  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strtok_multiple_delimiters) {
  char str1[] = "Hello,World;Test";
  char str2[] = "Hello,World;Test";

  char *expected = strtok(str1, ",;");
  char *got = s21_strtok(str2, ",;");

  while (expected != S21_NULL && got != S21_NULL) {
    ck_assert_str_eq(got, expected);

    expected = strtok(S21_NULL, ",;");
    got = s21_strtok(S21_NULL, ",;");
  }

  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strtok_many_delimiters) {
  char str1[] = ",,,Hello,,,World,,,";
  char str2[] = ",,,Hello,,,World,,,";

  char *expected = strtok(str1, ",");
  char *got = s21_strtok(str2, ",");

  while (expected != S21_NULL && got != S21_NULL) {
    ck_assert_str_eq(got, expected);

    expected = strtok(S21_NULL, ",");
    got = s21_strtok(S21_NULL, ",");
  }

  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char str1[] = "";
  char str2[] = "";

  char *expected = strtok(str1, " ");
  char *got = s21_strtok(str2, " ");

  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_strtok_no_delimiters) {
  char str1[] = "HelloWorld";
  char str2[] = "HelloWorld";

  char *expected = strtok(str1, " ");
  char *got = s21_strtok(str2, " ");

  ck_assert_str_eq(got, expected);

  expected = strtok(S21_NULL, " ");
  got = s21_strtok(S21_NULL, " ");

  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_c) {
  char s21[100] = {0}, orig[100] = {0};
  ck_assert_int_eq(s21_sprintf(s21, "%c", 'A'), sprintf(orig, "%c", 'A'));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%5c", 'B'), sprintf(orig, "%5c", 'B'));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%-5c", 'C'), sprintf(orig, "%-5c", 'C'));
  ck_assert_str_eq(s21, orig);
}
END_TEST

START_TEST(test_d) {
  char s21[100] = {0}, orig[100] = {0};

  ck_assert_int_eq(s21_sprintf(s21, "%d", 123), sprintf(orig, "%d", 123));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%d", -456), sprintf(orig, "%d", -456));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%d", 0), sprintf(orig, "%d", 0));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%d", INT_MIN),
                   sprintf(orig, "%d", (int)INT_MIN));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%+d", 42), sprintf(orig, "%+d", 42));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "% d", 42), sprintf(orig, "% d", 42));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%8d", 123), sprintf(orig, "%8d", 123));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%-8d", 123), sprintf(orig, "%-8d", 123));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%.5d", 42), sprintf(orig, "%.5d", 42));
  ck_assert_str_eq(s21, orig);

  short h = -123;
  ck_assert_int_eq(s21_sprintf(s21, "%hd", h), sprintf(orig, "%hd", h));
  ck_assert_str_eq(s21, orig);

  long l = 1234567890L;
  ck_assert_int_eq(s21_sprintf(s21, "%ld", l), sprintf(orig, "%ld", l));
  ck_assert_str_eq(s21, orig);
}
END_TEST

START_TEST(test_u) {
  char s21[100] = {0}, orig[100] = {0};

  ck_assert_int_eq(s21_sprintf(s21, "%u", 123u), sprintf(orig, "%u", 123u));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%u", UINT_MAX),
                   sprintf(orig, "%u", (unsigned int)UINT_MAX));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%10u", 42u), sprintf(orig, "%10u", 42u));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%.6u", 42u), sprintf(orig, "%.6u", 42u));
  ck_assert_str_eq(s21, orig);

  unsigned short hu = 65535;
  ck_assert_int_eq(s21_sprintf(s21, "%hu", hu), sprintf(orig, "%hu", hu));
  ck_assert_str_eq(s21, orig);

  unsigned long lu = 4294967295UL;
  ck_assert_int_eq(s21_sprintf(s21, "%lu", lu), sprintf(orig, "%lu", lu));
  ck_assert_str_eq(s21, orig);
}
END_TEST

START_TEST(test_f) {
  char s21[100] = {0}, orig[100] = {0};

  ck_assert_int_eq(s21_sprintf(s21, "%f", 3.14159),
                   sprintf(orig, "%f", 3.14159));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%f", -2.5), sprintf(orig, "%f", -2.5));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%.2f", 3.14159),
                   sprintf(orig, "%.2f", 3.14159));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%.0f", 3.6), sprintf(orig, "%.0f", 3.6));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%10.2f", 3.14),
                   sprintf(orig, "%10.2f", 3.14));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%+f", 3.14), sprintf(orig, "%+f", 3.14));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "% f", 3.14), sprintf(orig, "% f", 3.14));
  ck_assert_str_eq(s21, orig);
}
END_TEST

START_TEST(test_s) {
  char s21[100] = {0}, orig[100] = {0};

  ck_assert_int_eq(s21_sprintf(s21, "%s", "Hello"),
                   sprintf(orig, "%s", "Hello"));
  ck_assert_str_eq(s21, orig);

  s21_sprintf(s21, "%s", S21_NULL);
  ck_assert_str_eq(s21, "(null)");

  ck_assert_int_eq(s21_sprintf(s21, "%10s", "Hi"), sprintf(orig, "%10s", "Hi"));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%-10s", "Hi"),
                   sprintf(orig, "%-10s", "Hi"));
  ck_assert_str_eq(s21, orig);

  ck_assert_int_eq(s21_sprintf(s21, "%.3s", "Hello"),
                   sprintf(orig, "%.3s", "Hello"));
  ck_assert_str_eq(s21, orig);
}
END_TEST

START_TEST(test_percent) {
  char s21[100] = {0}, orig[100] = {0};
  ck_assert_int_eq(s21_sprintf(s21, "%%"), sprintf(orig, "%%"));
  ck_assert_str_eq(s21, orig);
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s = suite_create("s21_memchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memchr_found_begin);
  tcase_add_test(tc, test_memchr_found_middle);
  tcase_add_test(tc, test_memchr_not_found);
  tcase_add_test(tc, test_memchr_zero_n);
  tcase_add_test(tc, test_memchr_null_char);
  tcase_add_test(tc, test_memchr_unsigned_char);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memcmp_suite(void) {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcmp_equal);
  tcase_add_test(tc, test_memcmp_greater);
  tcase_add_test(tc, test_memcmp_less);
  tcase_add_test(tc, test_memcmp_zero_n);
  tcase_add_test(tc, test_memcmp_unsigned);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memcpy_suite(void) {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_memcpy_normal);
  tcase_add_test(tc, test_memcpy_with_null);
  tcase_add_test(tc, test_memcpy_zero_n);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_memset_suite(void) {
  Suite *s = suite_create("s21_memset");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_memset_normal);
  tcase_add_test(tc, test_memset_zero_n);
  tcase_add_test(tc, test_memset_partial);
  tcase_add_test(tc, test_memset_with_null);
  tcase_add_test(tc, test_memset_negative);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strncat_suite(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_strncat_normal);
  tcase_add_test(tc, test_strncat_partial);
  tcase_add_test(tc, test_strncat_zero_n);
  tcase_add_test(tc, test_strncat_empty_dest);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strchr_suite(void) {
  Suite *s = suite_create("s21_strchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strchr__first_occurrence);
  tcase_add_test(tc, test_strchr_end);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_null_terminator);
  tcase_add_test(tc, test_strchr_empty_string);
  tcase_add_test(tc, test_strchr_empty_string_null);
  tcase_add_test(tc, test_strchr_multiple_occurrences);
  tcase_add_test(tc, test_strchr_special_characters);
  tcase_add_test(tc, test_strchr_case_sensitive);
  tcase_add_test(tc, test_strchr_control_char);
  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strncmp_suite(void) {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncmp_equal_full);
  tcase_add_test(tc, test_strncmp_equal_within_n);
  tcase_add_test(tc, test_strncmp_greater);
  tcase_add_test(tc, test_strncmp_less);
  tcase_add_test(tc, test_strncmp_difference_after_n);
  tcase_add_test(tc, test_strncmp_prefix_n_greater);
  tcase_add_test(tc, test_strncmp_zero_n);
  tcase_add_test(tc, test_strncmp_empty_vs_nonempty);
  tcase_add_test(tc, test_strncmp_both_empty);
  tcase_add_test(tc, test_strncmp_case_sensitive);
  tcase_add_test(tc, test_strncmp_unsigned_char);
  tcase_add_test(tc, test_strncmp_with_null_in_middle);
  tcase_add_test(tc, test_strncmp_control_char);
  suite_add_tcase(s, tc);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strncpy_suite(void) {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_strncpy_src_longer_than_n);
  tcase_add_test(tc, test_strncpy_src_shorter_than_n);
  tcase_add_test(tc, test_strncpy_equal_length);
  tcase_add_test(tc, test_strncpy_zero_n);
  tcase_add_test(tc, test_strncpy_empty_src);
  tcase_add_test(tc, test_strncpy_unsigned_char);
  tcase_add_test(tc, test_strncpy_with_null_in_src);
  suite_add_tcase(s, tc);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strcspn_suite(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_strcspn_no_match);
  tcase_add_test(tc, test_strcspn_match_at_begin);
  tcase_add_test(tc, test_strcspn_match_middle);
  tcase_add_test(tc, test_strcspn_empty_reject);
  tcase_add_test(tc, test_strcspn_empty_str);
  tcase_add_test(tc, test_strcspn_control_chars);
  tcase_add_test(tc, test_strcspn_case_sensitive);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strerror_suite(void) {
  Suite *s = suite_create("s21_strerror");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_strerror_zero);
  tcase_add_test(tc, test_strerror_positive);
  tcase_add_test(tc, test_strerror_unknown);
  tcase_add_test(tc, test_strerror_negative);

  suite_add_tcase(s, tc);
  return s;
}

Suite *s21_strlen_suite(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strlen_normal);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_one_char);
  tcase_add_test(tc, test_strlen_spaces);
  tcase_add_test(tc, test_strlen_special_chars);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_strpbrk_suite(void) {
  Suite *s = suite_create("s21_strpbrk");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strpbrk_found_begin);
  tcase_add_test(tc, test_strpbrk_found_middle);
  tcase_add_test(tc, test_strpbrk_found_from_many);
  tcase_add_test(tc, test_strpbrk_not_found);
  tcase_add_test(tc, test_strpbrk_empty_str1);
  tcase_add_test(tc, test_strpbrk_empty_str2);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_strrchr_suite(void) {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strrchr_first_occurrence);
  tcase_add_test(tc, test_strrchr_last_occurrence);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_null_terminator);
  tcase_add_test(tc, test_strrchr_empty);
  tcase_add_test(tc, test_strrchr_empty_null);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_strstr_suite(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strstr_begin);
  tcase_add_test(tc, test_strstr_middle);
  tcase_add_test(tc, test_strstr_end);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_empty_haystack);
  tcase_add_test(tc, test_strstr_equal);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_strtok_suite(void) {
  Suite *s = suite_create("s21_strtok");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strtok_first_token);
  tcase_add_test(tc, test_strtok_all_tokens);
  tcase_add_test(tc, test_strtok_multiple_delimiters);
  tcase_add_test(tc, test_strtok_many_delimiters);
  tcase_add_test(tc, test_strtok_empty_string);
  tcase_add_test(tc, test_strtok_no_delimiters);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_c);
  tcase_add_test(tc, test_d);
  tcase_add_test(tc, test_u);
  tcase_add_test(tc, test_f);
  tcase_add_test(tc, test_s);
  tcase_add_test(tc, test_percent);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  SRunner *sr = srunner_create(s21_strchr_suite());
  srunner_add_suite(sr, s21_memchr_suite());
  srunner_add_suite(sr, s21_memcmp_suite());
  srunner_add_suite(sr, s21_memcpy_suite());
  srunner_add_suite(sr, s21_memset_suite());
  srunner_add_suite(sr, s21_strncat_suite());
  srunner_add_suite(sr, s21_strncmp_suite());
  srunner_add_suite(sr, s21_strncpy_suite());
  srunner_add_suite(sr, s21_strcspn_suite());
  srunner_add_suite(sr, s21_strerror_suite());
  srunner_add_suite(sr, s21_strlen_suite());
  srunner_add_suite(sr, s21_strpbrk_suite());
  srunner_add_suite(sr, s21_strrchr_suite());
  srunner_add_suite(sr, s21_strstr_suite());
  srunner_add_suite(sr, s21_strtok_suite());
  srunner_add_suite(sr, s21_sprintf_suite());

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  if (number_failed == 0) return EXIT_SUCCESS;
  return EXIT_FAILURE;
}