
struct operand
{
    char *first_operand;
    char *second_operand;
};

enum reg_type{
    reg_8,
    reg_16,
    reg_32,
    reg_mm,
    reg_xmm
};
struct input_data{
    int has_first;
    int has_second;

    enum reg_type first_reg_type;
    enum reg_type second_reg_type;
};

struct operand decode_modrm(struct input_data input);