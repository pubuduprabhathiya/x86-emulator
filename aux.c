#include "aux.h"
#include <assert.h>
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

struct test str_split(char *a_str, const char a_delim) {
  struct test output;
  char **result = 0;
  int count = 0;
  char *tmp = a_str;
  char *last_comma = 0;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

  while (*tmp) {
    if (a_delim == *tmp) {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  count += last_comma < (a_str + strlen(a_str) - 1);
  count++;

  result = malloc(sizeof(char *) * (count + 1));

  if (result) {
    size_t idx = 1;
    char *token = strtok(a_str, delim);

    while (token) {
      assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    assert(idx == count);
    *(result + idx) = 0;
  }

  output.argc = count;
  output.argv = result;
  return output;
}

void write_file(char *name, char *result) {
  FILE *fp;
  name = strcatn(3, BUFSIZ, "../output/", name, ".out");

  fp = fopen(name, "w");
  fputs(result, fp);
  fclose(fp);
}