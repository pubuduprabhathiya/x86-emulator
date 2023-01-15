#include "Immediate_grp_map.h"
#include "../byte_reader/reader.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcodes/add.h"
#include "opcode.h"
#include <string.h>

struct group {
  int group;
  int index;
};

map immediate_opcode_map_80[] = {&add80};
map immediate_opcode_map_81[] = {&add81};
map immediate_opcode_map_82[] = {&add82};
map immediate_opcode_map_83[] = {&add83};

map *immediate_opcode_map_group_1[] = {
    immediate_opcode_map_80, immediate_opcode_map_81, immediate_opcode_map_82,
    immediate_opcode_map_83};

map *immediate_opcode_map(struct group grp) {

  if (grp.group == 1) {
    return immediate_opcode_map_group_1[grp.index];
  }

  return NULL;
}
struct group get_group(unsigned char byte) {
  struct group grp;
  if (byte == 0X80 || byte == 0X81 || byte == 0X82 || byte == 0X83) {
    grp.group = 1;
    if (byte == 0X80)
      grp.index = 0;
    if (byte == 0X81)
      grp.index = 1;
    if (byte == 0X82)
      grp.index = 2;
    if (byte == 0X83)
      grp.index = 3;
    return grp;
  };
  return grp;
}
struct instruction decode_immediate(unsigned char byte) {
  unsigned char cur_byte = get_cur_byte();
  int second = (cur_byte & 0X38) >> 3;
  struct group grp = get_group(byte);
  struct instruction ins = immediate_opcode_map(grp)[second](cur_byte);
  return ins;
}