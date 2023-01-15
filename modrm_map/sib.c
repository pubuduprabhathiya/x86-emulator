#include "sib.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include <stdio.h>
#include <stdlib.h>

char *regs[] = {"EAX", "ECX", "EDX", "EBX", "ESP", "0X0", "ESI", "EDI"};

struct sib_output *decode_sib() {

  struct sib_output *out =
      (struct sib_output *)malloc(sizeof(struct sib_output));

  unsigned char byte = get_next_byte();
  int ss = byte >> 6;
  int index = (byte & 0X38) >> 3;
  int base = (byte & 0X07);

  printf("%i,%i,%i\n", ss, index, base);
  char *first;
  char *second;

  first = regs[base];
  if (index == 4) {
    second = "none";
  } else if (index == 5) {
    second = "EBP";
  } else {
    second = regs[index];
  }
  if (ss > 0) {
    char val[2];
    snprintf(val, BUFSIZ, "%i", ss);
    first = strcatn(7, BUFSIZ, "(%", first, ",%", second, ",", val, ")");
  } else {
    first = strcatn(5, BUFSIZ, "(%", first, ",%", second, ")");
  }
  out->output_string = first;
  return out;
}