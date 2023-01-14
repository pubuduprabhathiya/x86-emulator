#include "byte_reader/reader.h"
#include "opcode_map/opcode.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  init_registers();
  set_reader(argc, &argv);
  unsigned char byte = get_next_byte();
  decode(byte);
}