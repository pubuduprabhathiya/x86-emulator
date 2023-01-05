#include <stdio.h>


struct instruction
{
    char* opcode;
    struct operand *operands;
};

typedef struct instruction (*map)(unsigned char byte);

void decode(unsigned char  byte);

map *opcode_map(int byte);

void print_ins(struct instruction ins);