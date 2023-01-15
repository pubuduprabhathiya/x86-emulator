#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strcatn(unsigned nstr, unsigned max_len, ...) {
  unsigned n = 0, max = 64;
  char *out = calloc(max, max);

  va_list vargs;
  va_start(vargs, max_len);
  for (int i = 0; i < nstr; i++) {
    const char *s = va_arg(vargs, const char *);
    if (max <= n + strnlen(s, max_len)) {
      max = 3 * (n + strnlen(s, max_len)) / 2 + 1;
      out = realloc(out, max);
    }
    strncpy(out + n, s, strnlen(s, max_len));
    n += strnlen(s, max_len);
  }
  va_end(vargs);
  out[n] = '\0';
  return out;
}