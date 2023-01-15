#include "byte_reader/reader.h"
#include "opcode_map/opcode.h"
#include <stdio.h>
#include "register_module/register.h"
#include "memory_module/memory.h"

int main(int argc, char *argv[]) {
  init_registers();
  memory_init();

   enum reg_type type_of_reg = reg_32;
    char * reg_name = "EAX";

  Register_32 *reg_to_read =
    (Register_32*)get_register(type_of_reg,reg_name); 
    int b =*(reg_to_read->value);

    printf("read value from EAX : %x\n",b);
  
  set_reader(argc, &argv);
  unsigned char byte = get_next_byte();
  decode(byte);

   

     reg_to_read =(Register_32*)get_register(type_of_reg,reg_name); 
    b =*(reg_to_read->value);

    printf("read value from EAX : %x\n",b);
  
}