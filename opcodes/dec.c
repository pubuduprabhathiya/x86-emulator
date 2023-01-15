#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"
#include "dec.h"

struct instruction dec48(unsigned char byte){
    struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%EAX";
  Register_8 *reg = get_register(reg_32, "EAX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec49(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%ECX";
  Register_8 *reg = get_register(reg_32, "ECX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec4a(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%EDX";
  Register_8 *reg = get_register(reg_32, "EDX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec4b(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%EBX";
  Register_8 *reg = get_register(reg_32, "EBX");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec4c(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%ESP";
  Register_8 *reg = get_register(reg_32, "ESP");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec4d(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%EBP";
  Register_8 *reg = get_register(reg_32, "EBP");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec4e(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%ESI";
  Register_8 *reg = get_register(reg_32, "ESI");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}
struct instruction dec4f(unsigned char byte){
       struct instruction ins;
  struct modrm_output op ;
  ins.opcode = "dec";
  ins.operands = &op;
  op.first_string_opeands="%EDI";
  Register_8 *reg = get_register(reg_32, "EDI");

  uint32_t arg = (uint32_t)(reg->value - 1);
  *(reg->value) = arg;
      
    op.second_string_opeands="";
    ins.has_two=0;
  return ins;
}

struct instruction decfe(unsigned char byte){}
struct instruction decff(unsigned char byte){}