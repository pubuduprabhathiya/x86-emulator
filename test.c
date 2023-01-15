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
  // name=strcatn(2, BUFSIZ, "../sample/", name);
  FILE *ptr;
  ptr = fopen(strcatn(2, BUFSIZ, "../sample/", name), "r");

  if (NULL == ptr) {
    printf("file can't be opened \n");
    return;
  }
  struct test output;
  char str[255];
  char *temp=malloc(sizeof(char));
  while (fgets(str, 255, ptr) != NULL) {
    temp=strcpy(temp,str);
    output = str_split(str, ' ');
  }

  set_reader(output.argc, &output.argv);
  char *result =strcatn(2,BUFSIZ, temp,"\t\t");
  while (is_next()) {
    unsigned char byte = get_next_byte();
    char *ins = decode(byte);
    result = strcatn(2, BUFSIZ, result, ins);
  }
  printf("\nend test %s\n\n\n", name);
  write_file(name, result);

  fclose(ptr);
  free(output.argv);
  free(temp);
}

void write_file(char *name, char *result) {
  FILE *fp;
  name = strcatn(3, BUFSIZ, "../output/", name, ".out");

  fp = fopen(name, "w");
  // fprintf(fp, result);
  fputs(result, fp);
  fclose(fp);
}