#include <stdio.h>

#include "../opcodes/add.h"
#include "../opcodes/and.h"
#include "../opcodes/cmp.h"

struct instruction {
  char *opcode;
  struct modrm_output *operands;
};

typedef struct instruction (*map)(unsigned char byte);

char *decode(unsigned char byte);

map *opcode_map(int byte);

char *print_ins(struct instruction *ins);