#include <stdio.h>

#include "../opcodes/add.h"

struct instruction {
  char *opcode;
  struct modrm_output *operands;
};

typedef struct instruction (*map)(unsigned char byte);

void decode(unsigned char byte);

map *opcode_map(int byte);

void print_ins(struct instruction ins);