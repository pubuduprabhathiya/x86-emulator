#include "../byte_reader/reader.h"
#include "modrm_map.h"
#include <stdio.h>

const char* r8[8]={"AL", "CL","DL", "BL", "AH","CH" ,"DH","BH"};
const char* r16[8]={"AX", "CX","DX","BX","SP","BP","SI","DI"};
const char* r32[8]={"EAX", "ECX","EDX","EBX","ESP","EBP","ESI","EDI"};
const  char* mm[8]={"MM0","MM1","MM2","MM3","MM4","MM5","MM6","MM7"};
const char* xmm[8]={"XMM0","XMM1","XMM2","XMM3","XMM4","XMM5","XMM6","XMM7"};

char *get_reg(enum reg_type type,int index){
    if(type==reg_8){
        return (char *)r8[index];
    }
    else if (type== reg_16)
    {
        return (char *)r16[index];
    }
    else if (type==reg_32)
    {
       return (char *)r32[index];
    }
    else if (type==reg_mm)
    {
        return (char *)mm[index];
    }
    else{
        return (char *)xmm[index];
    }
    
    
    

}
 
struct operand  decode_modrm(struct input_data input){
    unsigned char byte = get_next_byte();
    int mod=byte>>6;
    int rm=(byte & 0X38)>>3;
    int reg=(byte & 0X07);
    struct operand op;
    if(input.has_first){
        op.first_operand=get_reg(input.first_reg_type,reg);
    }
    if(input.has_second){
        op.second_operand=get_reg(input.second_reg_type,reg);
    }
    return op;
}