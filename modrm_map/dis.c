#include "modrm_map.h"
#include "dis.h"
#include <string.h>
#include <stdlib.h>
#include "../aux.h"

char *displacement(int bits){
    unsigned int num_of_byte=bits/8;
    char *op=malloc(num_of_byte*2+2);
    for(int i=0;i<num_of_byte;i++){
        char *byte = get_next_byte_char();
        op=strcatn(2, num_of_byte*2+2, op,byte) ;
    }
    op=strcatn(2, num_of_byte*2+2, "0X",op) ;
    return op;
}