#include <stdio.h>

#include "../opcodes/add.h"
#include "../opcodes/and.h"
#include "../opcodes/cmp.h"
#include "../opcodes/inc.h"
#include "../opcodes/dec.h"
#include "../opcodes/mov.h"
#include "../opcodes/or.h"
#include "../opcodes/xor.h"
#include "../opcodes/sub.h"
#include "../opcodes/sbb.h"

struct instruction {
  char *opcode;
  struct modrm_output *operands;
  int has_two:1;
};

typedef struct instruction (*map)(unsigned char byte);

char *decode(unsigned char byte);

map *opcode_map(int byte);

char *print_ins(struct instruction *ins);