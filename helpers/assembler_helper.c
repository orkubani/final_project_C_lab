#include "assembler_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Set extra word for instruction based on the operand type. */
void set_inst_extra_words(Analyzed_line analyzed_line, Compiled_Line * compiled_line, int num_of_operands, int * address)
{
    unsigned int extra_word = 0;
    int i;

    for (i = 0; i < num_of_operands; i++) 
    {
        /* Const Number */
        if (analyzed_line.dir_or_inst.instruction.inst_operand_options[i] == operand_const_number)
        {
            extra_word = analyzed_line.dir_or_inst.instruction.inst_operands[i].const_number << ARE_INDENTATION;
            insert_word(compiled_line, extra_word, address);
        }

        /* Register */
        if(analyzed_line.dir_or_inst.instruction.inst_operand_options[i] == operand_register)
        {
            if (num_of_operands == 2 && 
                analyzed_line.dir_or_inst.instruction.inst_operand_options[0] == operand_register && 
                analyzed_line.dir_or_inst.instruction.inst_operand_options[1] == operand_register) 
            {
                
                extra_word = analyzed_line.dir_or_inst.instruction.inst_operands[0].register_number << SRC_REG_INDENTATION; /* SRC */
                extra_word |= analyzed_line.dir_or_inst.instruction.inst_operands[1].register_number << DEST_REG_INDENTATION; /* DEST */
                insert_word(compiled_line, extra_word, address);
                return;
            }

            else if(i == 0)
            {
                extra_word = analyzed_line.dir_or_inst.instruction.inst_operands[i].register_number << SRC_REG_INDENTATION;
                insert_word(compiled_line, extra_word, address);
            }

            else 
            {
                extra_word = analyzed_line.dir_or_inst.instruction.inst_operands[i].register_number << DEST_REG_INDENTATION;
                insert_word(compiled_line, extra_word, address);
            }   
        }

        if(analyzed_line.dir_or_inst.instruction.inst_operand_options[i] == operand_label)
        {
            if (num_of_operands == 1)
            {
                compiled_line->missing_label_op_type[0] = dest_label;
                strcpy(compiled_line->missing_label[0], analyzed_line.dir_or_inst.instruction.inst_operands[0].label);
                insert_word(compiled_line, '\0', address); /* Dummy. Will be changed later */
                return;
            }

            compiled_line->missing_label_op_type[i] = i;
            strcpy(compiled_line->missing_label[i], analyzed_line.dir_or_inst.instruction.inst_operands[i].label);
            insert_word(compiled_line, '\0', address); /* Dummy. Will be changed later */
        }
    }

    return;
}

/* generate assembler warning */
void assembler_warning(int line_index)
{
    printf("WARNING! Line Number '%d':\n", line_index);
    return;
}

/* generate assembler error */
void assembler_error(int line_index)
{
    printf("Error! Exit in Line Number '%d'\n", line_index);
    exit(0);
}