#include <klib.h>
#include <klib-macros.h>

#include <stdint.h>


#include <stdio.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t res = 0;
  while (s[res] != '\0') {
    res++;
  }
  return res;
}

char *strcpy(char *dst, const char *src) {
  for (int i = 0; i < strlen(src); i++) {  //注意拷贝末尾的'\0'
    dst[i] = src[i];
  }
  dst[strlen(src)] = '\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) 
    dst[i] = src[i];
  for ( ; i <= n; i++) 
    dst[i] = '\0';
  return dst;
}

char *
strcat(char *dest, const char *src)
{
  size_t dest_len = strlen(dest);
  size_t i;

  for (i = 0 ; src[i] != '\0' ; i++)
      dest[dest_len + i] = src[i];
  dest[dest_len + i] = '\0';

  return dest;
}

// int strcmp(const char *s1, const char *s2) {
//   size_t n = strlen(s1);
//   size_t m = strlen(s2);
//   for (size_t i = 0; i < (n > m ? m : n); i++) {
//     if (s1[i] < s2[i]) return -1;
//     if (s1[i] > s2[i]) return 1;
//   }
//   if (n == m) return 0;
//   return n < m ? -1 : 1;
// }

int strcmp(const char *s1, const char *s2) {
  unsigned char c1, c2;
  while (1) {
    c1 = *s1++;
    c2 = *s2++;
    if (c1 != c2) return c1 < c2 ? -1 : 1;
    if (!c1) break;
  }
  return 0;
  panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t l1 = strlen(s1);
  size_t l2 = strlen(s2);
  size_t l = l1 > l2 ? l2 : l1;
  for (size_t i = 0; i < (n > l ? l : n); i++) {
    if (s1[i] < s2[i]) return -1;
    if (s1[i] > s2[i]) return 1;
  }
  if (l < n) {
    if (l1 == l2) return 0;
    return l1 < l2 ? -1 : 1;
  }
  return 0;
}

void *memset(void *s, int c, size_t n) {
  if (s == NULL || n < 0) {
    return NULL;
  }
  unsigned char *tmp = (unsigned char *)s;
  for (size_t i = 0; i < n; i++) {
    *tmp = c;
    tmp ++;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  char tmp[n];
  char *srct = (char *)src;
  char *dstt = (char *)dst; 
  for (size_t i = 0; i < n; i++) tmp[i] = srct[i];
  for (size_t i = 0; i < n; i++) dstt[i] = tmp[i];
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  n = n / 8;
  uint64_t *srct = (uint64_t *)in;
  uint64_t *dstt = (uint64_t *)out;
  for (size_t i = 0; i < n; i++) dstt[i] = srct[i];
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  unsigned char *c1 = (unsigned char *)s1;
  unsigned char *c2 = (unsigned char *)s2;
  for (size_t i = 0; i < n; i++) {
    if (c1[i] < c2[i]) return -1;
    if (c1[i] > c2[i]) return 1;
  }
  //panic("return 0");
  return 0;
  panic("Not implemented");
}

#endif
