#include "add.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"

struct instruction add00(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 0, 1, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "add";
  ins.operands = &op;

  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);
    *(reg1->value) = (*reg1->value + *reg2->value);
  } else {

    struct Data data;
    data.type = UINT8;
    get_mem()->read(op.first_operand_effective_addr, &data);

    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);
    uint8_t arg = (uint8_t)(*data.value + *reg2->value);
    data.value = &arg;
    get_mem()->write(op.first_operand_effective_addr, &data);
  }

  return ins;
}
struct instruction add01(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 0, 1, reg_32, reg_32};
  struct modrm_output op = decode_modrm(input);

  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}
struct instruction add02(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 1, 0, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}
struct instruction add03(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 1, 0, reg_32, reg_32};

  struct modrm_output op = decode_modrm(input);
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}
struct instruction add04(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  struct displacement_output *dis_out = displacement(8);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  op.first_operand_register = "AL";
  op.first_string_opeands = "%AL";
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}
struct instruction add05(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  struct displacement_output *dis_out = displacement(32);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  op.first_operand_register = "EAX";
  op.first_string_opeands = "%EAX";
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}

struct instruction add80(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {0, 0, 0, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  struct displacement_output *dis_out = displacement(8);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}

struct instruction add81(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {0, 0, 0, reg_32, reg_32};

  struct modrm_output op = decode_modrm(input);
  struct displacement_output *dis_out = displacement(32);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}

struct instruction add82(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {0, 0, 0, reg_8, reg_8};

  struct modrm_output op = decode_modrm(input);
  struct displacement_output *dis_out = displacement(8);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}

struct instruction add83(unsigned char byte) {

  struct instruction ins;
  struct input_data input = {0, 0, 0, reg_32, reg_32};

  struct modrm_output op = decode_modrm(input);
  struct displacement_output *dis_out = displacement(8);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  ins.opcode = "add";
  ins.operands = &op;
  return ins;
}
