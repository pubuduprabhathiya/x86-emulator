#include "reader.h"
#include <stdio.h>
#include <stdlib.h>

unsigned next_byte = 1;
char **args;
int argsc = 0;

int is_next(){
  return next_byte < argsc;
}

unsigned char get_next_byte() {
  if (next_byte < argsc) {
    char *byte = args[next_byte];
    next_byte += 1;
    printf("read %s\n",byte);
    return strtol(byte, NULL, 16);
  }
  return NULL;
}
unsigned char get_cur_byte() {
  if (next_byte - 1 > 0) {
    char *byte = args[next_byte - 1];
    return strtol(byte, NULL, 16);
  }
  return NULL;
}
char *get_next_byte_char() {
  if (next_byte < argsc) {
    char *byte = args[next_byte];
    next_byte += 1;
    return byte;
  }
  return NULL;
}

void set_reader(int argc, char **argv[]) {
  args = *argv;
  argsc = argc;
}