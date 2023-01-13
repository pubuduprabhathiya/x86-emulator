#include <inttypes.h>

struct sib_output
{
    uint32_t effective_addr;
    char *output_string;
};


struct sib_output *decode_sib();