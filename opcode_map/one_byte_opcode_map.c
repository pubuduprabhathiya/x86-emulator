#include "../aux.h"
#include "../modrm_map/modrm_map.h"
#include "Immediate_grp_map.h"
#include "opcode.h"
#include <string.h>

map opcode_map_0[] = {&add00, &add01, &add02, &add03, &add04, &add05};
map opcode_map_1[] = {};
map opcode_map_2[] = {&and20, &and21, &and22, &and23, &and24, &and25};
map opcode_map_3[] = {};
map opcode_map_4[] = {};
map opcode_map_5[] = {};
map opcode_map_6[] = {};
map opcode_map_7[] = {};
map opcode_map_8[] = {&decode_immediate, &decode_immediate, &decode_immediate,
                      &decode_immediate};

map *opcode_map(int byte) {
  if (byte == 0) {
    return opcode_map_0;
  } else if (byte == 1) {
    return opcode_map_1;
  } else if (byte == 2) {
    return opcode_map_2;
  } else if (byte == 3) {
    return opcode_map_3;
  } else if (byte == 4) {
    return opcode_map_4;
  } else if (byte == 5) {
    return opcode_map_5;
  } else if (byte == 6) {
    return opcode_map_6;
  } else if (byte == 7) {
    return opcode_map_7;
  } else if (byte == 8) {
    return opcode_map_8;
  }

  return NULL;
}
char *decode(unsigned char byte) {
  int first = byte / 16;
  int second = byte % 16;
  struct instruction ins = opcode_map(first)[second](byte);
  // printf("test  %s %s,%s\n", ins->opcode,
  // ins->operands->second_string_opeands,
  //        ins->operands->first_string_opeands);
  char *result =
      strcatn(6, BUFSIZ, ins.opcode, " ", ins.operands->second_string_opeands,
              ", ", ins.operands->first_string_opeands, "\n");
  // print_ins(ins);
  printf("%s", result);
  return result;
}

char *print_ins(struct instruction *ins) {
  // printf("test  %s %s,%s\n", ins->opcode,
  // ins->operands->second_string_opeands,
  //        ins->operands->first_string_opeands);
}
