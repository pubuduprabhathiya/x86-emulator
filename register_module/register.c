#include <stdint.h>
#include <stdio.h>
#include "register.h"
#include <string.h>
// #include "../modrm_map/modrm_map.h"

const char* r8[8]={"AL", "CL","DL", "BL", "AH","CH" ,"DH","BH"};
const char* r16[8]={"AX", "CX","DX","BX","SP","BP","SI","DI"};
const char* r32[8]={"EAX", "ECX","EDX","EBX","ESP","EBP","ESI","EDI"};
const char* mm[8]={"MM0","MM1","MM2","MM3","MM4","MM5","MM6","MM7"};
const char* xmm[8]={"XMM0","XMM1","XMM2","XMM3","XMM4","XMM5","XMM6","XMM7"};

const char* eip[1] = {"EIP"};
const char* eflags[1] = {"EFLAGS"};

const char* cs[1] = {"CS"};
const char* ss[1] = {"SS"};
const char* ds[1] = {"DS"};
const char* es[1] = {"ES"};
const char* fs[1] = {"FS"};
const char* gs[1] = {"GS"};

Register_8** registers_r8 = NULL;
Register_16** registers_r16 = NULL;
Register_32** registers_r32 = NULL;
Register_64** registers_mm = NULL;
Register_128** registers_xmm = NULL;

Register_32** registers_eip = NULL;
Register_32** registers_eflags = NULL;

Register_16** registers_cs = NULL;
Register_16** registers_ss = NULL;
Register_16** registers_ds = NULL;
Register_16** registers_es = NULL;
Register_16** registers_fs = NULL;
Register_16** registers_gs = NULL;

void *get_register(enum reg_type type,char* reg_name);

void init_registers(){
    registers_r8 = (Register_8**)malloc(sizeof(Register_8*)*8);
    registers_r16 = (Register_16**)malloc(sizeof(Register_16*)*8);
    registers_r32 = (Register_32**)malloc(sizeof(Register_32*)*8);
    registers_mm = (Register_64**)malloc(sizeof(Register_64*)*8);
    registers_xmm = (Register_128**)malloc(sizeof(Register_128*)*8);

    registers_eip = (Register_32**)malloc(sizeof(Register_32*));
    registers_eflags = (Register_32**)malloc(sizeof(Register_32*));

    registers_cs = (Register_16**)malloc(sizeof(Register_16*));
    registers_ss = (Register_16**)malloc(sizeof(Register_16*));
    registers_ds = (Register_16**)malloc(sizeof(Register_16*));
    registers_es = (Register_16**)malloc(sizeof(Register_16*));
    registers_fs = (Register_16**)malloc(sizeof(Register_16*));
    registers_gs = (Register_16**)malloc(sizeof(Register_16*));

    for(int i = 0;i<8;i++){
        registers_r8[i] = (Register_8*)malloc(sizeof(Register_8));
    }
    for(int i = 0;i<8;i++){
        registers_r16[i] = (Register_16*)malloc(sizeof(Register_16));
    }
    for(int i = 0;i<8;i++){
        registers_r32[i] = (Register_32*)malloc(sizeof(Register_32));
    }
    for(int i = 0;i<8;i++){
        registers_mm[i] = (Register_64*)malloc(sizeof(Register_64));
    }
    for(int i = 0;i<8;i++){
        registers_xmm[i] = (Register_128*)malloc(sizeof(Register_128));
    }

    for(int i = 0;i<1;i++){
        registers_eip[i] = (Register_32*)malloc(sizeof(Register_32));
    }
    for(int i = 0;i<1;i++){
        registers_eflags[i] = (Register_32*)malloc(sizeof(Register_32));
    }

    for(int i = 0;i<1;i++){
        registers_cs[i] = (Register_16*)malloc(sizeof(Register_16));
    }
    for(int i = 0;i<1;i++){
        registers_ss[i] = (Register_16*)malloc(sizeof(Register_16));
    }
    for(int i = 0;i<1;i++){
        registers_ds[i] = (Register_16*)malloc(sizeof(Register_16));
    }
    for(int i = 0;i<1;i++){
        registers_es[i] = (Register_16*)malloc(sizeof(Register_16));
    }
    for(int i = 0;i<1;i++){
        registers_fs[i] = (Register_16*)malloc(sizeof(Register_16));
    }
    for(int i = 0;i<1;i++){
        registers_gs[i] = (Register_16*)malloc(sizeof(Register_16));
    }

    uint8_t intial_8[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for(int i=0;i<8;i++){
        registers_r8[i]->value = (uint8_t*)malloc(sizeof(uint8_t));
        registers_r8[i]->value[0] = intial_8[i];
    }

    uint16_t intial_16[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for(int i=0;i<8;i++){
        registers_r16[i]->value = (uint16_t*)malloc(sizeof(uint16_t));
        registers_r16[i]->value[0] = intial_16[i];
    }

    uint32_t intial_32[8] = {0xbf8db144, 0x88c5cffb, 0x1, 0xae5ff4, 0xbf8db0bc, 0xbf8db118, 0x9a0ca0, 0x0};
    for(int i=0;i<8;i++){
        registers_r32[i]->value = (uint32_t*)malloc(sizeof(uint32_t));
        registers_r32[i]->value[0] = intial_32[i];
    }

    uint64_t intial_mm[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for(int i=0;i<8;i++){
        registers_mm[i]->value = (uint64_t*)malloc(sizeof(uint64_t));
        registers_mm[i]->value[0] = intial_mm[i];
    }

    uint64_t intial_xmm[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for(int i=0;i<8;i++){
        registers_xmm[i]->value[0] = (uint64_t*)malloc(sizeof(uint64_t));
        registers_xmm[i]->value[1] = (uint64_t*)malloc(sizeof(uint64_t));
        registers_xmm[i]->value[0] = intial_xmm[i];
        registers_xmm[i]->value[1] = intial_xmm[i];
    }

    uint32_t initial_eip[1] = {0x8048354};
    registers_eip[0]->value = (uint32_t*)malloc(sizeof(uint32_t));
    registers_eip[0]->value[0] = initial_eip[0];

    uint32_t initial_eflag[1] = {0x246};
    registers_eflags[0]->value = (uint32_t*)malloc(sizeof(uint32_t));
    registers_eflags[0]->value[0] = initial_eflag[0];

    uint16_t initial_ss[1] = {0x7b};
    registers_ss[0]->value = (uint16_t*)malloc(sizeof(uint16_t));
    registers_ss[0]->value[0] = initial_ss[0];

    uint16_t initial_cs[1] = {0x73};
    registers_cs[0]->value = (uint16_t*)malloc(sizeof(uint16_t));
    registers_cs[0]->value[0] = initial_cs[0];
    
    uint16_t initial_ds[1] = {0x7b};
    registers_ds[0]->value = (uint16_t*)malloc(sizeof(uint16_t));
    registers_ds[0]->value[0] = initial_ds[0];

    uint16_t initial_es[1] = {0x7b};
    registers_es[0]->value = (uint16_t*)malloc(sizeof(uint16_t));
    registers_es[0]->value[0] = initial_es[0];

    uint16_t initial_fs[1] = {0x0};
    registers_fs[0]->value = (uint16_t*)malloc(sizeof(uint16_t));
    registers_fs[0]->value[0] = initial_fs[0];

    uint16_t initial_gs[1] = {0x33};
    registers_gs[0]->value = (uint16_t*)malloc(sizeof(uint16_t));
    registers_gs[0]->value[0] = initial_gs[0];

}


void *get_register(enum reg_type type,char* reg_name){
    if(type==reg_8){
        int i=0;
        for(i;i<8;i++){
            char *str1 = r8[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_r8[i];
            }
    
        }
    }
    if(type==reg_16){
        int i=0;
        for(i;i<8;i++){
            char *str1 = r16[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_r16[i];
            }
    
        }
    }
    if(type==reg_32){
        int i=0;
        for(i;i<8;i++){
            char *str1 = r32[i];
            char *str2 = reg_name;
            if(strcmp(str1,str2)==0){
                return registers_r32[i];
            }
    
        }
    }
    if(type==reg_mm){
        int i=0;
        for(i;i<8;i++){
            char *str1 = mm[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_mm[i];
            }
    
        }
    }
    if(type==reg_xmm){
        int i=0;
        for(i;i<8;i++){
            char *str1 = xmm[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_xmm[i];
            }
    
        }
    }

    if(type==reg_eip){
        int i=0;
        for(i;i<1;i++){
            char *str1 = eip[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_eip[i];
            }
    
        }
    }
    if(type==reg_eflags){
        int i=0;
        for(i;i<1;i++){
            char *str1 = eflags[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_eflags[i];
            }
    
        };
    }
    if(type==reg_cs){
        int i=0;
        for(i;i<1;i++){
            char *str1 = cs[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_cs[i];
            }
    
        }
    }
    if(type==reg_ss){
        int i=0;
        for(i;i<1;i++){
            char *str1 = ss[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_ss[i];
            }
    
        }
    }
    if(type==reg_ds){
        int i=0;
        for(i;i<1;i++){
            char *str1 = ds[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_ds[i];
            }
    
        }
    }
    if(type==reg_es){
        int i=0;
        for(i;i<1;i++){
            char *str1 = es[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_es[i];
            }
    
        }
    }
    if(type==reg_fs){
        int i=0;
        for(i;i<1;i++){
            char *str1 = fs[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_fs[i];
            }
    
        }
    }
    if(type==reg_gs){
        int i=0;
        for(i;i<1;i++){
            char *str1 = gs[i];
            char *str2 = reg_name;

            if(strcmp(str1,str2)==0){
                return registers_gs[i];
            }
    
        }
    }

    
    
}

void dump_registers(){
    printf("============================== GENERAL PURPOSE REGISTERS ==============================\n\n");
    printf("8-bit registers\n");
    for(int i=0;i<8;i++){
        printf("%s : 0x%02x\n",r8[i],registers_r8[i]->value[0]);
    }
    printf("\n");

    printf("16-bit registers\n");
    for(int i=0;i<8;i++){
        printf("%s : 0x%04x\n",r16[i],registers_r16[i]->value[0]);
    }
    printf("\n");

    printf("32-bit registers\n");
    for(int i=0;i<8;i++){
        printf("%s : 0x%08x\n",r32[i],registers_r32[i]->value[0]);
    }
    printf("\n");

    printf("64-bit registers\n");
    for(int i=0;i<8;i++){
        printf("%s : 0x%016x\n",mm[i],registers_mm[i]->value[0]);
    }
    printf("\n");

    printf("128-bit registers\n");
    for(int i=0;i<8;i++){
        printf("%s : 0x%016x%016x\n",xmm[i],registers_mm[i]->value[0],registers_mm[i]->value[1]);
    }
    printf("\n");

    printf("============================== SPECIAL PURPOSE REGISTERS ==============================\n\n");
    printf("%s : 0x%08x\n",eip[0],registers_eip[0]->value[0]);
    printf("%s : 0x%08x\n",eflags[0],registers_eflags[0]->value[0]);

    printf("\n");

    printf("%s : 0x%04x\n",ss[0],registers_ss[0]->value[0]);
    printf("%s : 0x%04x\n",cs[0],registers_cs[0]->value[0]);
    printf("%s : 0x%04x\n",ds[0],registers_ds[0]->value[0]);
    printf("%s : 0x%04x\n",es[0],registers_es[0]->value[0]);
    printf("%s : 0x%04x\n",fs[0],registers_fs[0]->value[0]);
    printf("%s : 0x%04x\n",gs[0],registers_gs[0]->value[0]);
}

int main(){

    init_registers();
    enum reg_type type_of_reg = reg_32;
    char * reg_name = "EAX";
    uint32_t a = 0x11145111;

    Register_32 *reg_to_write = (Register_32*)get_register(type_of_reg,reg_name);
    reg_to_write->value = &a;

    Register_32 *reg_to_read = (Register_32*)get_register(type_of_reg,reg_name);
    int b = *(reg_to_read->value);

    printf("read value from EAX : %x\n",b);

    enum reg_type reg_cs_type = reg_cs;
    char * reg_name_cs = "CS";

    int c = registers_cs[0]->value[0];

    printf("read value from CS : %x\n",registers_cs[0]->value[0]);

    dump_registers();

    return 0;
}