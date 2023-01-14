#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
  enum Type { UINT8, UINT16, UINT32, UINT64 } type;
  uint64_t *value;
};

struct Memory {
  int hashtablesize;
  uint32_t *hashtable;
  uint64_t *values;

  void (*write)(uint32_t *address, struct Data *data);

  void (*read)(uint32_t *address, struct Data *data);

  int (*cell_index)(uint32_t *address);

  void (*extend_hashtable)();

  void (*dump)();
};

void memory_init();

struct Memory *get_mem();