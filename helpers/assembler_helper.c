#include "assembler_helper.h"

/* Set extra word for instruction based on the operand type. */
void set_inst_extra_word(Analyzed_line analyzed_line, Compiled_Line * compiled_line, int operand_i)
{
    unsigned int extra_word = 0;

    /* Const Number */
    if (analyzed_line.dir_or_inst.instruction.inst_operand_options[operand_i] == operand_const_number)
    {
        extra_word = analyzed_line.dir_or_inst.instruction.inst_operands[operand_i].const_number << ARE_INDENTATION;
        insert_word(compiled_line, extra_word);
        return;
    }

}