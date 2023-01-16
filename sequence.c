#include "aux.h"
#include "byte_reader/reader.h"
#include "opcode_map/opcode.h"
#include "register_module/register.h"
#include "test.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_sequence(char *name) {
  printf("==============================start sequence %s "
         "==============================\n\n",
         name);
  // name=strcatn(2, BUFSIZ, "../sample/", name);
  FILE *ptr;
  ptr = fopen(name, "r");

  if (NULL == ptr) {
    printf("file can't be opened \n");
    return;
  }
  struct test output;
  char str[255];
  char *temp = malloc(sizeof(char));
  while (fgets(str, 255, ptr) != NULL) {
    temp = strcpy(temp, str);
    output = str_split(str, ' ');
  }

  set_reader(output.argc, &output.argv);
  char *result = strcatn(2, BUFSIZ, temp, "\n\n");
  while (is_next()) {
    unsigned char byte = get_next_byte();
    char *ins = decode(byte);
    result = strcatn(2, BUFSIZ, result, ins);
  }
  printf("\n============================== end sequence %s "
         "==============================\n\n\n",
         name);
  write_file(name, result);

  free(ptr);
  free(output.argv);
  free(temp);
}
