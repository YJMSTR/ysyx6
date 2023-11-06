#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  /*
  Some programs imprudently rely on code such as the following

      sprintf(buf, "%s some further text", buf);

  to append text to buf.  However, the standards explicitly note that the results are undefined if source and destination buffers overlap when  calling  sprintf(),  snprintf(),
  vsprintf(), and vsnprintf().  Depending on the version of gcc(1) used, and the compiler options employed, calls such as the above will not produce the expected results.

  The  glibc implementation of the functions snprintf() and vsnprintf() conforms to the C99 standard, that is, behaves as described above, since glibc version 2.1.  Until glibc
  2.0.6, they would return -1 when the output was truncated.
  */
  va_list ap;
  va_start(ap, fmt);
  uint32_t len = strlen(fmt);
  int cur = 0;
  for (int i = 0; i < len; i++) {
    if (fmt[i] == '%') {
      if (i + 1 < len) {
        switch (fmt[i+1]) {
          case 'd': 
            int tmp = va_arg(ap, int);
            char stk[35];
            int stk_top = 0, f = 1;
            while (tmp != 0) {
              if (tmp < 0) {
                f = -1;
                tmp = -tmp;
              }
              stk[++stk_top] = (tmp % 10) + '0';
              tmp /= 10;
            }
            if (f < 0) out[cur++] = '-';
            while (stk_top > 0) {
              out[cur++] = stk[stk_top];
              stk_top--; 
            }
            i++;
            break;
          case 's':
            char *tmpstr = va_arg(ap, char*);
            int j = 0;
            while (tmpstr[j] != '\0') {
              out[cur++] = tmpstr[j];
              j++;
            }
            i++;
            break;
        }
      }
      continue;
    } else {
      out[cur++] = fmt[i];
    } 
  }  
  out[cur] = '\0';
  va_end(ap);
  return cur;
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
