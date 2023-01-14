
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
struct input_data{
    int has_first;
    int has_second;

    int is_first_reg;
    int is_second_reg;

    enum reg_type first_reg_type;
    enum reg_type second_reg_type;
};

struct operand decode_modrm(struct input_data input);