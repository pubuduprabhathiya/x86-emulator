#include "sub.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"

struct instruction sub28(unsigned char byte) {

  struct instruction ins;
  struct input_data input = {1, 0, 1, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "sub";
  ins.operands = &op;

  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);
    *(reg2->value) = (*reg2->value - *reg1->value);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    data->type = UINT8;
    data->value = malloc(sizeof(uint8_t));
    get_mem()->read(&op.first_operand_effective_addr, data);

    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);

    uint8_t arg = (uint8_t)((uint8_t)*data->value - *reg2->value);
    data->type = UINT8;
    data->value = &arg;
    get_mem()->write(&op.first_operand_effective_addr, data);
  }
  ins.has_two = 1;
  return ins;
}

struct instruction sub29(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 0, 1, reg_32, reg_32};
  struct modrm_output op = decode_modrm(input);

  ins.opcode = "sub";
  ins.operands = &op;

  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);
    *(reg2->value) = (*reg2->value - *reg1->value);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    data->type = UINT32;
    data->value = malloc(sizeof(u_int32_t));
    get_mem()->read(&op.first_operand_effective_addr, data);

    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);

    u_int32_t arg = (u_int32_t)((u_int32_t)*data->value - *reg2->value);
    data->type = UINT8;
    data->value = &arg;
    get_mem()->write(&op.first_operand_effective_addr, data);
  }
  ins.has_two = 1;
  return ins;
}

struct instruction sub2a(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 1, 0, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "sub";
  ins.operands = &op;

  if (op.is_second_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);
    *(reg1->value) = (*reg1->value - *reg2->value);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    ;
    data->type = UINT8;
    data->value = malloc(sizeof(uint8_t));
    get_mem()->read(&op.second_operand_effective_addr, data);

    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    u_int32_t arg = (u_int32_t)(*reg1->value - (u_int32_t)*data->value);
    *(reg1->value) = arg;
  }
  ins.has_two = 1;
  return ins;
}

struct instruction sub2b(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 1, 0, reg_32, reg_32};

  struct modrm_output op = decode_modrm(input);
  ins.opcode = "sub";
  ins.operands = &op;

  if (op.is_second_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    Register_32 *reg2 =
        get_register(op.second_reg_type, op.second_operand_register);
    *(reg1->value) = (*reg1->value - *reg2->value);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    ;
    data->type = UINT32;
    data->value = malloc(sizeof(uint32_t));
    get_mem()->read(&op.second_operand_effective_addr, data);

    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);

    u_int32_t arg = (u_int32_t)(*reg1->value - *data->value);
    *(reg1->value) = arg;
  }
  ins.has_two = 1;
  return ins;
}

struct instruction sub2c(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  struct displacement_output *dis_out = displacement(8);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  op.first_operand_register = "AL";
  op.first_string_opeands = "%AL";
  ins.opcode = "sub";
  ins.operands = &op;

  Register_8 *reg1 = get_register(reg_8, op.first_operand_register);

  uint8_t arg = (uint8_t)(reg1->value - (int8_t)dis_out->address);
  *(reg1->value) = arg;
  ins.has_two = 1;
  return ins;
}

struct instruction sub2d(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  struct displacement_output *dis_out = displacement(32);
  op.second_operand_register = dis_out->address;
  op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
  op.first_operand_register = "EAX";
  op.first_string_opeands = "%EAX";
  ins.opcode = "sub";
  ins.operands = &op;

  Register_32 *reg1 = get_register(reg_32, op.first_operand_register);

  uint32_t arg = (uint32_t)(reg1->value - dis_out->address);
  *(reg1->value) = arg;
  ins.has_two = 1;
  return ins;
}
