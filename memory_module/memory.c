// #include <glib.h>
#include "memory.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static struct Memory *mem;

void write(uint32_t *address, struct Data *data) {
  int cell_index = mem->cell_index(address);

  if (data->type == UINT8) {
    uint64_t value = *((uint64_t *)data->value) & 0x00000000000000FF;
    mem->values[cell_index] = value;
  }
  if (data->type == UINT16) {
    uint64_t value = *((uint64_t *)data->value) & 0x000000000000FFFF;
    mem->values[cell_index] = value;
  }
  if (data->type == UINT32) {
    uint64_t value = *((uint64_t *)data->value) & 0x00000000FFFFFFFF;

    mem->values[cell_index] = value;
  }
  if (data->type == UINT64) {
    uint64_t value = *((uint64_t *)data->value) & 0xFFFFFFFFFFFFFFFF;
    mem->values[cell_index] = value;
  }

  mem->hashtable[cell_index] = *address;
}

void read(uint32_t *address, struct Data *data) {
  int cell_index = mem->cell_index(address);
  if (data->type == UINT8) {
    uint8_t value = mem->values[cell_index] & 0xFF;
    *(uint8_t *)data->value = value;
  }
  if (data->type == UINT16) {
    uint16_t value = mem->values[cell_index] & 0xFFFF;
    *(uint16_t *)data->value = value;
  }
  if (data->type == UINT32) {
    uint32_t value = mem->values[cell_index] & 0xFFFFFFFF;
    *(uint32_t *)data->value = value;
  }
  if (data->type == UINT64) {
    uint64_t value = mem->values[cell_index] & 0xFFFFFFFFFFFFFFFF;
    *(uint64_t *)data->value = value;
  }
}

int cell_index(uint32_t *address) {

  int hashtablesize = mem->hashtablesize;

  for (int i = 0; i < hashtablesize; i++) {

    if (mem->hashtable[i] == *address) {
      return i;
    }
  }
  mem->extend_hashtable(mem);

  return mem->hashtablesize - 1;
}

void extend_hashtable() {
  int hashtablesize = mem->hashtablesize;

  uint32_t *new_hashtable =
      (uint32_t *)malloc(sizeof(uint32_t) * (hashtablesize + 1));
  uint64_t *new_values =
      (uint64_t *)malloc(sizeof(uint64_t) * (hashtablesize + 1));

  memset(new_hashtable, 0, (hashtablesize + 1) * sizeof(uint32_t));
  memset(new_values, 0, (hashtablesize + 1) * sizeof(uint64_t));

  for (int i = 0; i < hashtablesize; i++) {
    new_hashtable[i] = mem->hashtable[i];
  }

  for (int i = 0; i < hashtablesize; i++) {
    new_values[i] = mem->values[i];
  }

  mem->hashtable = new_hashtable;
  mem->hashtablesize += 1;
  mem->values = new_values;
}

void dump() {
  int hashtablesize = mem->hashtablesize;

  for (int i = 0; i < hashtablesize; i++) {
    printf("Memory Address: %x, \t Value: %llx\n", mem->hashtable[i],
           mem->values[i]);
  }
  printf("Memory dump success\n");
}

void memory_init() {
  mem = (struct Memory *)malloc(sizeof(struct Memory));
  mem->hashtable = (uint32_t *)malloc(sizeof(uint32_t));
  mem->values = (uint64_t *)malloc(sizeof(uint64_t));

  memset(mem->hashtable, 0, sizeof(uint32_t) * 1);
  memset(mem->values, 0, sizeof(uint64_t) * 1);

  mem->hashtablesize = 0;

  mem->cell_index = cell_index;
  mem->dump = dump;
  mem->extend_hashtable = extend_hashtable;
  mem->read = read;
  mem->write = write;
}

struct Memory *get_mem() {
  return mem;
}

// int main(){

//     uint32_t *addresses[4];
//     uint32_t a1=10,a2=20,a3=30,a4=40;
//     addresses[0] = &a1;
//     addresses[1] = &a2;
//     addresses[2] = &a3;
//     addresses[3] = &a4;

//     struct Data *values_to_write[4];
//     struct Data d1,d2,d3,d4;

//     d1.type=UINT32;
//     d1.value = malloc(sizeof(uint32_t));
//     *(uint32_t*)d1.value=0x11111111;

//     d2.type=UINT64;
//     d2.value = malloc(sizeof(uint64_t));
//     *(uint64_t*)d2.value = 0x222222222222222;

//     d3.type=UINT8;
//     d3.value = malloc(sizeof(uint8_t));
//     *(uint8_t*)d3.value = 0x33;

//     d4.type=UINT16;
//     d4.value = malloc(sizeof(uint16_t));
//     *(uint16_t*)d4.value = 0x4444;

//     values_to_write[0] = &d1;
//     values_to_write[1] = &d2;
//     values_to_write[2] = &d3;
//     values_to_write[3] = &d4;

//     mem->hashtable = (uint32_t*)malloc(sizeof(uint32_t));
//     mem->values = (uint64_t*)malloc(sizeof(uint64_t));

//     memset(mem->hashtable,0,sizeof(uint32_t)*1);
//     memset(mem->values,0,sizeof(uint64_t)*1);

//     mem->hashtablesize=0;

//     mem->cell_index = cell_index;
//     mem->dump = dump;
//     mem->extend_hashtable = extend_hashtable;
//     mem->read = read;
//     mem->write = write;

//     printf("Writing to memory\n");

//     for(int i=0;i<4;i++){
//         mem->write(addresses[i],values_to_write[i],mem);
//     }

//     mem->dump(mem);

//     struct Data *values_to_read[4];
//     struct Data r1,r2,r3,r4;

//     r1.type=UINT32;
//     r1.value = malloc(sizeof(uint32_t));
//     // *(uint32_t*)d1.value=0x11111111;

//     r2.type=UINT64;
//     r2.value = malloc(sizeof(uint64_t));
//     // *(uint64_t*)d2.value = 0x222222222222222;

//     r3.type=UINT8;
//     r3.value = malloc(sizeof(uint8_t));
//     // *(uint8_t*)d3.value = 0x33;

//     r4.type=UINT16;
//     r4.value = malloc(sizeof(uint16_t));
//     // *(uint16_t*)d4.value = 0x4444;

//     values_to_read[0] = &r1;
//     values_to_read[1] = &r2;
//     values_to_read[2] = &r3;
//     values_to_read[3] = &r4;

//     printf("\n");
//     printf("Reading from memory\n");

//     for(int i=0;i<4;i++){
//         mem->read(addresses[i],values_to_read[i],mem);
//     }

//     for(int i=0;i<4;i++){
//         printf("Memory Address: %x, \t Value:
//         %llx\n",addresses[i][0],values_to_read[i]->value[0]);
//     }

//     return 0;
// }
