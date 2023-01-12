#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

struct Data{
    enum Type {UINT8,UINT16,UINT32,UINT64} type;
    uint64_t* value;
};

struct Memory{
    int hashtablesize;
    uint32_t *hashtable;
    uint64_t *values;


    void (*write)(uint32_t *address, struct Data *data, struct Memory *mem);

    void (*read)(uint32_t *address, struct Data *data, struct Memory *mem);

    int (*cell_index)(uint32_t *address, struct Memory *mem);

    void (*extend_hashtable)(struct Memory *mem);

    void (*dump)(struct Memory *mem);

};

void write(uint32_t *address, struct Data *data, struct Memory *mem){

    int cell_index = mem->cell_index(address,mem);

    if(data->type==UINT8){
        uint64_t value = *((uint64_t*)data->value) & 0x00000000000000FF;
        mem->values[cell_index]=value;
    }
    if(data->type==UINT16){
        uint64_t value = *((uint64_t*)data->value) & 0x000000000000FFFF;
        mem->values[cell_index]=value;
    }
    if(data->type==UINT32){
        uint64_t value = *((uint64_t*)data->value) & 0x00000000FFFFFFFF;
        mem->values[cell_index]=value;
    }
    if(data->type==UINT64){
        uint64_t value = *((uint64_t*)data->value) & 0xFFFFFFFFFFFFFFFF;
        mem->values[cell_index]=value;
    }
    
    mem->hashtable[cell_index]=*address;
}

void read(uint32_t *address, struct Data *data, struct Memory *mem){

    int cell_index = mem->cell_index(address,mem);

    if(data->type==UINT8){
        uint8_t value = mem->values[cell_index] & 0xFF;
        *(uint8_t*)data->value=value;
    }
    if(data->type==UINT16){
        uint16_t value = mem->values[cell_index] & 0xFFFF;
        *(uint16_t*)data->value=value;
    }
    if(data->type==UINT32){
        uint32_t value = mem->values[cell_index] & 0xFFFFFFFF;
        *(uint32_t*)data->value=value;
    }
    if(data->type==UINT64){
        uint64_t value = mem->values[cell_index] & 0xFFFFFFFFFFFFFFFF;
        *(uint64_t*)data->value=value;
    }

}

int cell_index(uint32_t *address, struct Memory *mem){
    int hashtablesize = mem->hashtablesize;

    for(int i;i<hashtablesize;i++){
        if(mem->hashtable[i]==*address){
            return i;
        }
    }
    mem->extend_hashtable(mem);

    return mem->hashtablesize-1;
}

void extend_hashtable(struct Memory *mem){
    int hashtablesize = mem->hashtablesize;

    uint32_t *new_hashtable = (uint32_t*)malloc(sizeof(uint32_t)*(hashtablesize+1));
    uint64_t *new_values = (uint64_t*)malloc(sizeof(uint64_t)*(hashtablesize+1));

    memset(new_hashtable, 0, (hashtablesize+1) * sizeof(uint32_t));
    memset(new_values, 0, (hashtablesize+1) * sizeof(uint64_t));

    for(int i;i<hashtablesize;i++){
        new_hashtable[i] = mem->hashtable[i];
    }

    for(int i;i<hashtablesize;i++){
        new_values[i] = mem->values[i];
    }

    mem->hashtable = new_hashtable;
    mem->hashtablesize+=1;
    mem->values = new_values;

}

void dump(struct Memory *mem){
    int hashtablesize = mem->hashtablesize;

    for(int i;i<hashtablesize;i++){
        printf("Memory Address: %x, \t Value: %llx\n",mem->hashtable[i],mem->values[i]);
    }
    printf("Memory dump success\n");
}