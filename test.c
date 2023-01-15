#include "test.h"
#include "aux.h"
#include "byte_reader/reader.h"
#include "opcode_map/opcode.h"
#include "register_module/register.h"
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct test {
  int argc;
  char **argv;
};

void run_test() {
  DIR *d;
  struct dirent *dir;
  d = opendir("../sample");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == 8) {

        char *temp = malloc(sizeof(char));
        strcpy(temp, dir->d_name);
        execute_test(temp);
      }
    }
    closedir(d);
  }
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
void execute_test(char *name) {
  printf("start test %s\n\n", name);
  FILE *ptr;
  ptr = fopen(strcatn(2, BUFSIZ, "../sample/", name), "r");

  if (NULL == ptr) {
    printf("file can't be opened \n");
    return;
  }
  struct test output;
  char str[255];
  while (fgets(str, 255, ptr) != NULL) {
    output = str_split(str, ' ');
  }

  set_reader(output.argc, &output.argv);

  while (is_next()) {
    unsigned char byte = get_next_byte();
    decode(byte);
  }
  fclose(ptr);
  free(output.argv);
  printf("\nend test %s\n\n\n", name);
}