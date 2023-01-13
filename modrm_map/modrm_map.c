#include "modrm_map.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "dis.h"
#include "sib.h"
#include <stdio.h>

const char *r8[8] = {"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"};
const char *r16[8] = {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"};
const char *r32[8] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};
const char *mm[8] = {"MM0", "MM1", "MM2", "MM3", "MM4", "MM5", "MM6", "MM7"};
const char *xmm[8] = {"XMM0", "XMM1", "XMM2", "XMM3",
                      "XMM4", "XMM5", "XMM6", "XMM7"};

char *get_reg(enum reg_type type, int index) {
  if (type == reg_8) {
    return (char *)r8[index];
  } else if (type == reg_16) {
    return (char *)r16[index];
  } else if (type == reg_32) {
    return (char *)r32[index];
  } else if (type == reg_mm) {
    return (char *)mm[index];
  } else {
    return (char *)xmm[index];
  }
}
void get_rm(int mod, int rm, enum reg_type type, struct modrm_output *output,
            int isfirst) {
  struct sib_output *sib_out;
  if (mod != 3 && rm == 4) {
    sib_out = decode_sib();
  }
  if (mod == 0) {
    if (isfirst) 
        output->is_first_operand_register = 0;
    else output->is_second_operand_register=0;

    if (rm == 4) {
      if (isfirst) {
        output->first_operand_effective_addr = sib_out->effective_addr;
        output->first_string_opeands = sib_out->output_string;
      } else
        output->is_second_operand_register = 0;
    } else if (rm == 5) {
      struct displacement_output *dis = displacement(32);
      if (isfirst) {
        output->first_operand_effective_addr = dis->address;
        output->first_string_opeands =
            strcatn(2, BUFSIZ, "$", dis->print_output);
      }
    } else {

      // Need to implement

      //  get_reg(type,rm);
      //  if(isfirst){
      //     output->first_operand_effective_addr=dis->address;
      //     output->first_string_opeands=strcatn(2,BUFSIZ,"$",
      //     dis->print_output);
      // }
    }

  } else if (mod == 1) {
    if (isfirst) 
        output->is_first_operand_register = 0;
    else output->is_second_operand_register=0;

    struct displacement_output *dis = displacement(8);
    if (rm == 4) {
        if(isfirst){
        output->first_operand_effective_addr=sib_out->effective_addr+dis->address;
        output->first_string_opeands=strcatn(5, BUFSIZ, "$", dis->print_output, sib_out->output_string);
        }
    } else {
        if(isfirst){
       // output->first_operand_effective_addr=sib_out->effective_addr+dis->address;
        //output->first_string_opeands=strcatn(5, BUFSIZ, "$", dis->print_output, sib_out->output_string);
        }
      //char *sec = get_reg(type, rm);
      //return strcatn(5, BUFSIZ, "$", displacement(8), "(%", sec, ")");
    }

    /* code */
  } else if (mod == 2) {
    if (isfirst) 
        output->is_first_operand_register = 0;
    else output->is_second_operand_register=0;

     struct displacement_output *dis = displacement(32);
    if (rm == 4) {
        if(isfirst){
        output->first_operand_effective_addr=sib_out->effective_addr+dis->address;
        output->first_string_opeands=strcatn(5, BUFSIZ, "$", dis->print_output, sib_out->output_string);
        }
    } else {
        if(isfirst){
       // output->first_operand_effective_addr=sib_out->effective_addr+dis->address;
        //output->first_string_opeands=strcatn(5, BUFSIZ, "$", dis->print_output, sib_out->output_string);
        }
      //char *sec = get_reg(type, rm);
      //return strcatn(5, BUFSIZ, "$", displacement(8), "(%", sec, ")");
    }
    //char *sec = get_reg(type, rm);
   // return strcatn(5, BUFSIZ, "$", displacement(32), "(%", sec, ")");
  } else {
    if (isfirst) 
        output->is_first_operand_register = 1;
    else output->is_second_operand_register=1;

   // return get_reg(type, rm);
  }
}
struct modrm_output decode_modrm(struct input_data input) {
  unsigned char byte = get_next_byte();
  int mod = byte >> 6;
  int reg = (byte & 0X38) >> 3;
  int rm = (byte & 0X07);
  struct modrm_output output;

  if (input.is_first_reg) {
    output.first_operand_register = get_reg(input.first_reg_type, reg);
    output.is_first_operand_register = 1;
    output.first_string_opeands = strcatn(2,BUFSIZ,"%" , output.first_operand_register);
  } else {
    get_rm(mod, rm, input.first_reg_type, &output, 1);
    output.is_first_operand_register = 0;
  }

  if (input.has_second) {
    if (input.is_second_reg) {
      output.second_operand_register = get_reg(input.second_reg_type, reg);
      output.is_second_operand_register = 1;
      output.second_string_opeands = strcatn(2,BUFSIZ,"%" , output.second_operand_register);
    } else {
      get_rm(mod, rm, input.second_reg_type, &output, 0);
      output.is_second_operand_register = 0;
    }
  }
    printf("%s, %s \n",output.first_string_opeands,output.second_string_opeands);
  return output;
}