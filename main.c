#include "byte_reader/reader.h"
#include "memory_module/memory.h"
#include "opcode_map/opcode.h"
#include "register_module/register.h"
#include "test.h"
#include <stdio.h> 

int main(int argc, char *argv[]) {
  init_registers();
  memory_init();

  if(argc>1){
    if(!strncmp("-t",argv[1],2)){
      run_test();
      return 0;

    }
    else if (!strncmp("-s",argv[1],2))
    {
     return 0;
    }
    
  }
  printf("%i\n",argc);
  set_reader(argc, &argv);
  while (is_next())
  {
    unsigned char byte = get_next_byte();
    decode(byte);
  }
  
  

 
  return 0;
}