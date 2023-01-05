#include "opcode.h"
#include "../modrm_map/modrm_map.h"
#include <string.h>
# include "Immediate_grp_map.h"
#include "../opcodes/add.h"


map opcode_map_0[]={&add00,&add01,&add02,&add03,&add04,&add05};
map opcode_map_8[]={&decode_immediate,&decode_immediate,&decode_immediate,&decode_immediate};

map *opcode_map(int byte){
    if(byte==0){
        return opcode_map_0;
    }
    else if (byte==8)
    {
         return opcode_map_8;
    }
    
    return NULL;
}
void decode(unsigned char byte){
    int first=byte/16;
    int second=byte%16;
    struct instruction ins=opcode_map(first)[second](byte);
    print_ins(ins);
}

void print_ins(struct instruction ins){
    printf("%s %%%s, %%%s\n",ins.opcode,ins.operands->first_operand,ins.operands->second_operand);
}

