#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// struct cell{
//     uint64_t value;
// }
#define IS_uint8(x) (sizeof(x)==sizeof(uint8_t))
#define IS_uint16(x) (sizeof(x)==sizeof(uint16_t))
#define IS_uint32(x) (sizeof(x)==sizeof(uint32_t))
#define IS_uint64(x) (sizeof(x)==sizeof(uint64_t))

struct Memory{
    uint32_t *hashtable;
    uint64_t *values;
    // cell *mcells;

    void (*write)(uint32_t *address, void *data, struct Memory *mem);
    // void (*write)(uint32_t address, uint8_t data);
    // void (*write)(uint32_t address, uint16_t data);
    // void (*write)(uint32_t address, uint32_t data);
    // void (*write)(uint32_t address, uint64_t data);

    void (*read)(uint32_t *address, int *bits, struct Memory *mem);
    // uint8_t (*read)(uint32_t address);
    // uint16_t (*read)(uint32_t address);
    // uint32_t (*read)(uint32_t address);
    // uint64_t (*read)(uint32_t address);

    int (*cell_index)(uint32_t *address, struct Memory *mem);

    void (*extend_hashtable)(struct Memory *mem);

    void (*dump)(struct Memory *mem);

};


void write(uint32_t *address, void *data, struct Memory *mem){

    int cell_index = mem->cell_index(address,mem);

    if(IS_uint8(*data)){
        uint8_t value = (uint8_t)data;
        mem->values[cell_index]=value;
    }
    if(IS_uint16(*data)){
        uint16_t value = (uint16_t)data;
        mem->values[cell_index]=value;
    }
    if(IS_uint32(*data)){
        uint32_t value = (uint32_t)data;
        mem->values[cell_index]=value;
    }
    if(IS_uint64(*data)){
        uint64_t value = (uint64_t)data;
        mem->values[cell_index]=value;
    }
    // else{
    //     printf("%i",sizeof(*data));
    //     uint64_t value = 0;
    // }

    

    mem->hashtable[cell_index]=address;
    
}

void read(uint32_t *address, int *bits, struct Memory *mem){
    int cell_index = mem->cell_index(address, mem);
    if(*bits==8){
        uint8_t x;
        uint8_t *data = &x;
        *data = mem->values[cell_index];
        return data;
    }
    if(*bits==16){
        uint16_t x;
        uint16_t *data = &x;
        *data = mem->values[cell_index];
        return data;
    }
    if(*bits==32){
        uint32_t x;
        uint32_t *data = &x;
        *data = mem->values[cell_index];
        return data;
    }
    if(*bits==64){
        uint64_t x;
        uint64_t *data = &x;
        *data = mem->values[cell_index];
        return data;
    }

}

int cell_index(uint32_t *address, struct Memory *mem){
    int hashtablesize = sizeof(mem->hashtable)/sizeof(uint32_t);

    for(int i;i<hashtablesize;i++){
        if(mem->hashtable[i]==*address){
            return i;
        }
    }
    mem->extend_hashtable(mem);

    printf("cell_index success\n");
    return hashtablesize+1;
}

void extend_hashtable(struct Memory *mem){
    int hashtablesize = sizeof(mem->hashtable)/sizeof(uint32_t);

    uint32_t x;
    uint32_t *new_hashtable = &x;

    uint64_t y;
    uint64_t *new_values = &y;

    new_hashtable = (uint32_t*)malloc(sizeof(uint32_t)*(hashtablesize+1));
    new_values = (uint64_t*)malloc(sizeof(uint64_t)*(hashtablesize+1));

    for(int i;i<hashtablesize;i++){
        new_hashtable[i]=mem->hashtable[i];
    }

    for(int i;i<hashtablesize;i++){
        new_values[i]=mem->values[i];
    }

    mem->hashtable = new_hashtable;
    mem->values = new_values;

    printf("extent_hashtable success\n");
}

void dump(struct Memory *mem){
    int hashtablesize = sizeof(mem->hashtable)/sizeof(uint32_t);
    for(int i;i<hashtablesize;i++){
        printf("Memory Address: %u, \t Value: %llu\n",mem->hashtable[i],mem->values[i]);
    }
    printf("dump success\n");
}