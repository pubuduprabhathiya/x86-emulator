
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"
#include "cmp.h"

struct instruction cmp38(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 0, 1, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "cmp";
  ins.operands = &op;

  Register_8 *reg2 = get_register(op.second_reg_type, op.second_operand_register);
      
  if (op.is_first_operand_register) {
    Register_8 *reg1 =get_register(op.first_reg_type, op.first_operand_register);
       
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    data->type = UINT8;
    data->value = malloc(sizeof(uint8_t));
    get_mem()->read(&op.first_operand_effective_addr, data);

  }
ins.has_two=1;
  return ins;
}

struct instruction cmp39(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 0, 1, reg_32, reg_32};
  struct modrm_output op = decode_modrm(input);

  ins.opcode = "cmp";
  ins.operands = &op;

  Register_32 *reg2 =
      get_register(op.second_reg_type, op.second_operand_register);
  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.first_reg_type, op.first_operand_register);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    data->type = UINT32;
    data->value = malloc(sizeof(uint32_t));
    get_mem()->read(&op.first_operand_effective_addr, data);

  }
ins.has_two=1;
  return ins;
}

struct instruction cmp3a(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 1, 0, reg_8, reg_8};
  struct modrm_output op = decode_modrm(input);
  ins.opcode = "cmp";
  ins.operands = &op;

  Register_8 *reg2 =
      get_register(op.first_reg_type, op.first_operand_register);

  if (op.is_first_operand_register) {
    Register_8 *reg1 =
        get_register(op.second_reg_type, op.second_operand_register);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    data->type = UINT8;
    data->value = malloc(sizeof(uint8_t));
    get_mem()->read(&op.first_operand_effective_addr, data);

  }
ins.has_two=1;
  return ins;
}
struct instruction cmp3b(unsigned char byte) {
  struct instruction ins;
  struct input_data input = {1, 1, 0, reg_32, reg_32};

  struct modrm_output op = decode_modrm(input);
  ins.opcode = "cmp";
  ins.operands = &op;

  Register_32 *reg2 =
      get_register(op.first_reg_type, op.first_operand_register);

  if (op.is_first_operand_register) {
    Register_32 *reg1 =
        get_register(op.second_reg_type, op.second_operand_register);
  } else {
    struct Data *data = malloc(sizeof(struct Data));
    data->type = UINT32;
    data->value = malloc(sizeof(uint32_t));
    get_mem()->read(&op.first_operand_effective_addr, data);
  }
ins.has_two=1;
  return ins;
}