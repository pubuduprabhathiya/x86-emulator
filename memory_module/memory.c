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
  mem->extend_hashtable(address);

  return mem->hashtablesize - 1;
}

void extend_hashtable(uint32_t *address) {
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
  mem->hashtable[mem->hashtablesize - 1] = *address;
}

void dump() {
  int hashtablesize = mem->hashtablesize;

  for (int i = 0; i < hashtablesize; i++) {
    printf("Memory Address: %x, \t Value: %lx\n", mem->hashtable[i],
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
