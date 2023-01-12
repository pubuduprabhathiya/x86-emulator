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


// typedef struct Data Data;
// typedef struct Memory Memory;


void write(uint32_t *address, struct Data *data, struct Memory *mem){

    int cell_index = mem->cell_index(address,mem);

    if(data->type==UINT8){
        uint64_t value = *((uint64_t*)data->value) & 0x00000000000000FF;
        //printf("%llx\n",mem->values[cell_index]);
        mem->values[cell_index]=value;
    }
    if(data->type==UINT16){
        uint64_t value = *((uint64_t*)data->value) & 0x000000000000FFFF;
        //printf("%llx\n",mem->values[cell_index]);
        mem->values[cell_index]=value;
    }
    if(data->type==UINT32){
        uint64_t value = *((uint64_t*)data->value) & 0x00000000FFFFFFFF;
        //printf("%llx\n",mem->values[cell_index]);
        mem->values[cell_index]=value;
    }
    if(data->type==UINT64){
        uint64_t value = *((uint64_t*)data->value) & 0xFFFFFFFFFFFFFFFF;
        //printf("%llx\n",mem->values[cell_index]);
        mem->values[cell_index]=value;
    }
    
    mem->hashtable[cell_index]=*address;
}

void read(uint32_t *address, struct Data *data, struct Memory *mem){

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

    //printf("extend_hashtable : new_hashtable,new_values : initiation succeeded\n");

    memset(new_hashtable, 0, (hashtablesize+1) * sizeof(uint32_t));
    memset(new_values, 0, (hashtablesize+1) * sizeof(uint64_t));

    //printf("extend_hashtable : new_hashtable,new_values : setting memory to 0 succeeded\n");

    for(int i;i<hashtablesize;i++){
        new_hashtable[i] = (uint32_t)malloc(sizeof(uint32_t));
        // memset(new_hashtable[i], 0, sizeof(uint32_t));
        new_hashtable[i] = mem->hashtable[i];
    }

    //printf("extend_hashtable : new_hashtable : moving values succeeded\n");

    for(int i;i<hashtablesize;i++){
        new_values[i] = (uint64_t)malloc(sizeof(uint64_t));
        // memset(new_values[i], 0, sizeof(uint64_t));
        new_values[i] = mem->values[i];
    }

    //printf("extend_hashtable : new_values : moving values succeeded\n");

    mem->hashtable = new_hashtable;
    mem->hashtablesize+=1;
    mem->values = new_values;

    //printf("extend_hashtable : mem->hashtable,mem->values : assigning new values succeeded\n");

}

void dump(struct Memory *mem){
    int hashtablesize = mem->hashtablesize;

    for(int i;i<hashtablesize;i++){
        printf("Memory Address: %x, \t Value: %llx\n",mem->hashtable[i],mem->values[i]);
    }
    printf("Memory dump success\n");
}