#include "converter.h"
#include <stdio.h>

int byte_2_decimal(char byte[]) {
  int val = 0;
  if (&byte[0] >= '0' && &byte[0] <= '9') {
    val = &byte[0] - 48;
  } else if (&byte[0] >= 'a' && &byte[0] <= 'f') {
    val = &byte[0] - 97 + 10;
  } else if (&byte[0] >= 'A' && &byte[0] <= 'F') {
    val = &byte[0] - 65 + 10;
  }

  return val;
}