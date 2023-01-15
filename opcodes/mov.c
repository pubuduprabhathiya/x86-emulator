#include "mov.h"
#include "../aux.h"
#include "../byte_reader/reader.h"
#include "../memory_module/memory.h"
#include "../modrm_map/dis.h"
#include "../modrm_map/modrm_map.h"
#include "../opcode_map/opcode.h"

struct instruction mova0(unsigned char byte) {
    struct instruction ins;
    struct modrm_output op;

    // FULL DISPLACEMENT - 32 bit
    struct displacement_output *dis_out = displacement(32);
    op.second_operand_register = dis_out->address;
    op.second_string_opeands = strcatn(2, BUFSIZ, "$", dis_out->print_output);
    op.first_operand_register = "AL";
    op.first_string_opeands = "%AL";
    ins.opcode = "mov";
    ins.operands = &op;

    // EMULATION
    if (op.is_first_operand_register) {
        Register_8 *reg1 = get_register(op.first_reg_type, op.first_operand_register);
        Register_8 *reg2 = get_register(op.second_reg_type, op.second_operand_register);
        *(reg1->value) = (*reg1->value + *reg2->value);
    } else {
        struct Data *data;
        data->type = UINT8;
        data->value = malloc(sizeof(uint8_t));
        get_mem()->read(&op.first_operand_effective_addr, data);

        Register_32 *reg2 = get_register(op.second_reg_type, op.second_operand_register);

        uint8_t arg = (uint8_t)((uint8_t)data->value + *reg2->value);
        data->type = UINT8;
        data->value = &arg;
        get_mem()->write(&op.first_operand_effective_addr, data);
    }

    return ins;
}