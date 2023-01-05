#include "../opcode_map/opcode.h"
#include "../byte_reader/reader.h"
#include "../modrm_map/modrm_map.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/dis.h"
#include "add.h"

struct instruction add00(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,1,0,1,reg_8,reg_8};
    struct operand op= decode_modrm(input);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}
struct instruction add01(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,1,0,1,reg_32,reg_32};
    struct operand op= decode_modrm(input);
    
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}
struct instruction add02(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,1,1,0,reg_8,reg_8};
    struct operand op= decode_modrm(input);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}
struct instruction add03(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,1,1,0,reg_32,reg_32};

    struct operand op= decode_modrm(input);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}
struct instruction add04(unsigned char byte){
    struct instruction ins;
    struct operand op;
    op.second_operand=displacement(8);
    op.first_operand="AL";
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}
struct instruction add05(unsigned char byte){
    struct instruction ins;
    struct operand op;
    op.second_operand=displacement(32);
    op.first_operand="EAX";
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}

struct instruction add80(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,0,0,0,reg_8,reg_8};
    struct operand op= decode_modrm(input);
    op.second_operand=displacement(8);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}

struct instruction add81(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,0,0,0,reg_32,reg_32};

    struct operand op= decode_modrm(input);
    op.second_operand=displacement(32);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}

struct instruction add82(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,0,0,0,reg_8,reg_8};

    struct operand op= decode_modrm(input);
    op.second_operand=displacement(8);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}

struct instruction add83(unsigned char byte){
    struct instruction ins;
    struct input_data input={1,0,0,0,reg_32,reg_32};

    struct operand op= decode_modrm(input);
    op.second_operand=displacement(8);
    ins.opcode="add";
    ins.operands=&op;
    return ins;
}