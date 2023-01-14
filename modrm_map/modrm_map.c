#include "modrm_map.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "dis.h"
#include "sib.h"
#include <stdio.h>

void get_rm(int mod, int rm, enum reg_type type, char **resistertype,
            int *isregister, uint32_t *effective_addr, char **output_str) {
  struct sib_output *sib_out;
  if (mod != 3 && rm == 4) {
    sib_out = decode_sib();
  }
  *resistertype = get_reg_name(reg_32, rm);

  if (mod == 0) {
    *isregister = 0;

    if (rm == 4) {
      *effective_addr = sib_out->effective_addr;
      *output_str = sib_out->output_string;

    } else if (rm == 5) {
      struct displacement_output *dis = displacement(32);
      *effective_addr = dis->address;
      *output_str = strcatn(2, BUFSIZ, "$", dis->print_output);
            
    } else {

      Register_32 *reg_to_read = get_register(reg_32, *resistertype);
      *effective_addr = *(reg_to_read->value);
      *output_str = strcatn(3, BUFSIZ, "(%", *resistertype, ")");
    }
  } else if (mod == 1) {
    *isregister = 0;

    struct displacement_output *dis = displacement(8);
    if (rm == 4) {
      *effective_addr = sib_out->effective_addr + dis->address;
      *output_str =
          strcatn(5, BUFSIZ, "$", dis->print_output, sib_out->output_string);
    } else {
      Register_32 *reg_to_read = get_register(reg_32, *resistertype);
      *effective_addr = *(reg_to_read->value) + dis->address;
      *output_str =
          strcatn(5, BUFSIZ, "$", dis->print_output, "(%", *resistertype, ")");
    }
  } else if (mod == 2) {
    *isregister = 0;

    struct displacement_output *dis = displacement(32);
    if (rm == 4) {
      *effective_addr = sib_out->effective_addr + dis->address;
      *output_str =
          strcatn(5, BUFSIZ, "$", dis->print_output, sib_out->output_string);
    } else {
      Register_32 *reg_to_read = get_register(reg_32, *resistertype);
      *effective_addr = *(reg_to_read->value) + dis->address;
      *output_str =
          strcatn(5, BUFSIZ, "$", dis->print_output, "(%", *resistertype, ")");
    }
  } else {
    *isregister = 1;
    *resistertype = get_reg_name(type, rm);
    *output_str = strcatn(2, BUFSIZ, "%", *resistertype);
  }

}
struct modrm_output decode_modrm(struct input_data input) {
  unsigned char byte = get_next_byte();
  int mod = byte >> 6;
  int reg = (byte & 0X38) >> 3;
  int rm = (byte & 0X07);
  struct modrm_output output;

  if (input.is_first_reg) {
    output.first_operand_register = get_reg_name(input.first_reg_type, reg);
    output.is_first_operand_register = 1;
    output.first_string_opeands =
        strcatn(2, BUFSIZ, "%", output.first_operand_register);
    printf("%s \n", output.first_string_opeands);
  } else {
    get_rm(mod, rm, input.first_reg_type, &output.first_operand_register,
           &output.is_first_operand_register,
           &output.first_operand_effective_addr, &output.first_string_opeands);
  }

  if (input.has_second) {
    if (input.is_second_reg) {
      output.second_operand_register = get_reg_name(input.second_reg_type, reg);
      output.is_second_operand_register = 1;
      output.second_string_opeands =
          strcatn(2, BUFSIZ, "%", output.second_operand_register);
    } else {
      get_rm(mod, rm, input.first_reg_type, &output.second_operand_register,
             &output.is_second_operand_register,
             &output.second_operand_effective_addr,
             &output.second_string_opeands);
    }
  }
  return output;
}