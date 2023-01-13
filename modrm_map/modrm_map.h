#include <inttypes.h>
struct modrm_output
{
    int is_first_operand_register;
    int is_second_operand_register;

    uint32_t first_operand_effective_addr;
    uint32_t second_operand_effective_addr;

    char *first_operand_register;
    char *second_operand_register;

    char *first_string_opeands;
    char *second_string_opeands;
};

enum reg_type{
    reg_8,
    reg_16,
    reg_32,
    reg_mm,
    reg_xmm
};
struct input_data{
    int has_second;

    int is_first_reg;
    int is_second_reg;

    enum reg_type first_reg_type;
    enum reg_type second_reg_type;
};

struct modrm_output decode_modrm(struct input_data input);