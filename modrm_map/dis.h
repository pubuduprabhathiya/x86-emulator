#include <stdio.h>
#include "../byte_reader/reader.h"
#include <inttypes.h>

struct displacement_output
{
    uint32_t address;
    char *print_output;
};


struct displacement_output *displacement(int bits);