
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"
#include "inc.h"

struct instruction inc40(unsigned char byte) {
  struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%EAX";
  Register_8 *reg = get_register(reg_32, "EAX");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc41(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%ECX";
  Register_8 *reg = get_register(reg_32, "ECX");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc42(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%EDX";
  Register_8 *reg = get_register(reg_32, "EDX");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc43(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%EBX";
  Register_8 *reg = get_register(reg_32, "EBX");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc44(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%ESP";
  Register_8 *reg = get_register(reg_32, "ESP");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc45(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%EBP";
  Register_8 *reg = get_register(reg_32, "EBP");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc46(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%ESI";
  Register_8 *reg = get_register(reg_32, "ESI");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction inc47(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "inc";
  ins.operands = &op;
  op.first_string_opeands="%EDI";
  Register_8 *reg = get_register(reg_32, "EDI");

  uint32_t arg = (uint32_t)(reg->value + 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}