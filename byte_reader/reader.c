#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

unsigned next_byte = 1;
char **args;
int argsc = 0;

unsigned char get_next_byte() {
  if (next_byte < argsc) {
    char *byte = args[next_byte];
    next_byte += 1;
    return strtol(byte,NULL,16);
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

void set_reader(int argc, char **argv[]){
args = *argv;
argsc = argc;
 
}