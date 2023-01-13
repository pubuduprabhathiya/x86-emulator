#include "dis.h"
#include "../aux.h"
#include "modrm_map.h"
#include <stdlib.h>
#include <string.h>

struct displacement_output *displacement(int bits) {
  struct displacement_output out;
  unsigned int num_of_byte = bits / 8;
  char *op = malloc(num_of_byte * 2 + 2);
  for (int i = 0; i < num_of_byte; i++) {
    char *byte = get_next_byte_char();
    op = strcatn(2, num_of_byte * 2 + 2, byte, op);
  }
  out.address = strtol(op, NULL, 16);
  snprintf(op, num_of_byte * 2 + 2, "%lX", strtol(op, NULL, 16));
  out.print_output = strcatn(2, num_of_byte * 2 + 2, "0X", op);
  return &out;
}