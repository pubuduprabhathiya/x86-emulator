#include "opcode.h"
#include "../modrm_map/modrm_map.h"
#include <string.h>

struct instruction add00(){
    struct instruction ins;
    struct input_data input;
    input.first_reg_type=reg_32;
    input.second_reg_type=reg_32;
    input.has_first=1;
    input.has_second=1;
    struct operand op= decode_modrm(input);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}

map opcode_map_0[]={&add00};

map *opcode_map(int byte){
    if(byte==0){
        return opcode_map_0;
    }
    return NULL;
}
void decode(unsigned char byte){
    int first=byte/16;
    int second=byte%16;
    struct instruction ins=opcode_map(first)[second]();
    print_ins(ins);
}

void print_ins(struct instruction ins){
    printf("%s %%%s, %%%s\n",ins.opcode,ins.operands->first_operand,ins.operands->second_operand);
}

