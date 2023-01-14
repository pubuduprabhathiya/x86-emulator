#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum reg_type {
  reg_8,
  reg_16,
  reg_32,
  reg_mm,
  reg_xmm,
  reg_eip,
  reg_eflags,
  reg_cs,
  reg_ss,
  reg_ds,
  reg_es,
  reg_fs,
  reg_gs
};

typedef struct Register_8 {
  uint8_t *value;
} Register_8;

typedef struct Register_16 {
  uint16_t *value;
} Register_16;

typedef struct Register_32 {
  uint32_t *value;
} Register_32;

typedef struct Register_64 {
  uint64_t *value;
} Register_64;

typedef struct Register_128 {
  uint64_t *value[2];
} Register_128;

void init_registers();
char *get_reg_name(enum reg_type type, int index);
void *get_register(enum reg_type type, char *reg_name);