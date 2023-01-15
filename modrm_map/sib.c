#include "sib.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../register_module/register.h"
#include "dis.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char *regs[] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};

struct sib_output *decode_sib(int mod) {

  struct sib_output *out =
      (struct sib_output *)malloc(sizeof(struct sib_output));

  unsigned char byte = get_next_byte();
  int ss = byte >> 6;
  int index = (byte & 0X38) >> 3;
  int base = (byte & 0X07);

  char *first;
  char *second;

  first = regs[base];

  char val[2];
  ss = pow(2, ss);

  snprintf(val, BUFSIZ, "%i", ss);

  if (index == 4) {
    second = "";
  } else {
    second = regs[index];
    Register_32 *reg_to_read = get_register(reg_32, second);
    out->effective_addr = *reg_to_read->value * ss;
    second = strcatn(2, BUFSIZ, "%", second);
  }
  if (base == 5) {
    if (mod == 0) {
      struct displacement_output *dis = displacement(32);
      out->effective_addr += dis->address;
      out->output_string =
          strcatn(5, BUFSIZ, "(", dis->print_output, "(", second, "))");
    } else if (mod == 1) {
      struct displacement_output *dis = displacement(8);
      out->effective_addr += dis->address;
      Register_32 *ebp = get_register(reg_32, "EBP");
      out->effective_addr += *ebp->value;
      out->output_string =
          strcatn(5, BUFSIZ, "(", dis->print_output, "(%EBP", second, "))");
    } else if (mod == 2) {
      struct displacement_output *dis = displacement(32);
      out->effective_addr += dis->address;
      Register_32 *ebp = get_register(reg_32, "EBP");
      out->effective_addr += *ebp->value;
      out->output_string =
          strcatn(5, BUFSIZ, "(", dis->print_output, "(%EBP", second, "))");
    }

  } else {
    Register_32 *b = get_register(reg_32, first);
    out->effective_addr += *b->value;
    out->output_string =
        strcatn(7, BUFSIZ, "(%", first, ",", second, ",", val, ")");
  }
  // if (index != 4) {
  //   Register_32 *reg_to_read = get_register(reg_32, second);
  //   out->effective_addr = *reg_to_read->value*ss;
  //   first = strcatn(7, BUFSIZ, "(%", first, ",%", second, ",", val, ")");
  // } else {
  //   first = strcatn(7, BUFSIZ, "(%", first, ",", second, ",", val, ")");
  // }
  return out;
}