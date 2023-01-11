// #include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include "memory.h"


struct Memory memobj;
struct Memory *mem = &memobj;

// uint32_t *addresses[2];
// uint32_t a1=10,a2=20;
// addresses[0] = (uint32_t*)&a1;
// addresses[1] = (uint32_t*)&a2;

// uint64_t *values_to_write[2];
// uint64_t v1=10,v2=20;
// values_to_write[0] = (uint64_t*)&v1;
// values_to_write[1] = (uint64_t*)&v2;

int main(){

    uint32_t *addresses[2];
    uint32_t a1=10,a2=20;
    addresses[0] = (uint32_t*)&a1;
    addresses[1] = (uint32_t*)&a2;

    uint64_t *values_to_write[2];
    uint64_t v1=10,v2=20;
    values_to_write[0] = (uint64_t*)&v1;
    values_to_write[1] = (uint64_t*)&v2;
    
    mem->hashtable = (uint32_t*)malloc(sizeof(uint32_t));
    mem->values = (uint64_t*)malloc(sizeof(uint64_t));

    mem->cell_index = cell_index;
    mem->dump = dump;
    mem->extend_hashtable = extend_hashtable;
    mem->read = read;
    mem->write = write;

    for(int i=0;i<sizeof(values_to_write)/sizeof(uint64_t);i++){
        mem->write(addresses[i],values_to_write[i],mem);
    }

    mem->dump(mem);
    return 0;
}

