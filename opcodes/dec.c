#include "dec.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"

struct instruction dec48(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%EAX";
  Register_8 *reg = get_register(reg_32, "EAX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec49(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%ECX";
  Register_8 *reg = get_register(reg_32, "ECX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec4a(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%EDX";
  Register_8 *reg = get_register(reg_32, "EDX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec4b(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%EBX";
  Register_8 *reg = get_register(reg_32, "EBX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec4c(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%ESP";
  Register_8 *reg = get_register(reg_32, "ESP");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec4d(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%EBP";
  Register_8 *reg = get_register(reg_32, "EBP");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec4e(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%ESI";
  Register_8 *reg = get_register(reg_32, "ESI");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction dec4f(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands = "%EDI";
  Register_8 *reg = get_register(reg_32, "EDI");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;

  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}

struct instruction decfe(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {0, 0, 0, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "dec";
  ins.operands = &op;

  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    *(reg1->value) = (*reg1->value - 1);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    ;
    data->type = UINT8;
    data->value = malloc(sizeof(uint8_t));
    get_mem()->read(&op.second_operand_effective_addr, data);

    u_int8_t arg = (u_int8_t)((u_int8_t)*data->value - 1);
    data->type = UINT8;
    data->value = &arg;
    get_mem()->write(&op.first_operand_effective_addr, data);
  }
  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}
struct instruction decff(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {0, 0, 0, reg_32, reg_32};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "dec";
  ins.operands = &op;

  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
    *(reg1->value) = (*reg1->value - 1);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    ;
    data->type = UINT32;
    data->value = malloc(sizeof(uint32_t));
    get_mem()->read(&op.second_operand_effective_addr, data);

    uint32_t arg = (uint32_t)((uint32_t)*data->value - 1);
    data->type = UINT32;
    data->value = &arg;
    get_mem()->write(&op.first_operand_effective_addr, data);
  }
  op.second_string_opeands = "";
  ins.has_two = 0;
  return ins;
}