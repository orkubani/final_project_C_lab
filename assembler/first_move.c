#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>

/* First move on the am_file. */
int first_move(FILE * am_file/*, Object_File * object_file*/, const char * am_filename)
{
    char line[MAX_LINE_LENGTH] = {0}; /* Initilize line */
    Analyzed_line analyzed_line;
    Compiled_Line * data_section = NULL;
    Compiled_Line * code_section = NULL;
    Compiled_Line * current_compiled_line = NULL;
    int line_index = 1;
    unsigned int word = 0;

    while (fgets(line, sizeof(line), am_file)) 
    {
        analyzed_line = get_analyzed_line(line);

        if (is_valid_analyzed_line(&analyzed_line) == FALSE)
        {
            printf("Error in line '%d'! %s\n", line_index, analyzed_line.syntax_error);
            line_index++;
            continue;
        }

        /* Handle Main Label Here */

        if (analyzed_line.analyzed_line_opt == directive)
        {
            /* Implement Here */
            line_index++;
            continue;
        }

        else if (analyzed_line.analyzed_line_opt == instruction) 
        {
            code_section = insert_compiled_line_to_table(code_section, line_index);

            /* Define the instruction word */
            word = analyzed_line.dir_or_inst.instruction.inst_operand_options[DEST_OPERAND_I] << DEST_INDENTATION;
            word |= analyzed_line.dir_or_inst.instruction.inst_operand_options[SRC_OPERAND_I] << SRC_INDENTATION;
            word |= analyzed_line.dir_or_inst.instruction.inst_opt << OPCODE_INDENTATION;
            
            /* Add the instruction word to the relevant compiled_line in the code_section */
            current_compiled_line = get_compiled_line(code_section, line_index);
            insert_word(current_compiled_line, word);

            line_index++;
            continue;
        }

        /* First Move failed */
        line_index++;
        return FALSE;
    } 

    return TRUE;
}