#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "../modrm_map/modrm_map.h"


typedef struct Register_8{
    uint8_t* value;
} Register_8;

typedef struct Register_16{
    uint16_t* value;
} Register_16;

typedef struct Register_32{
    uint32_t* value;
} Register_32;

typedef struct Register_64{
    uint64_t* value;
} Register_64;

typedef struct Register_128{
    uint64_t* value[2];
} Register_128;


void *get_register(enum reg_type type,char* reg_name);
void init_registers();
void dump_registers();