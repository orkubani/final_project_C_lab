#include "analyzer.h"
#include <stdlib.h>
#include <string.h>


 int is_dir_or_inst(char *line)
 {
    /* Default for testing */
    return DIR_ENUM_CODE;
 }


Analyzed_line get_analyzed_line(char *line)
{
    Analyzed_line analyzed_line;
    int line_type;

    asm_instruction asm_all_instructions[NUM_OF_INST] = 
    {
    /* {<inst_name>, <inst_key>, <immed_as_src>, <label_as_src>, <reg_as_src>, <immed_as_dest>, <label_as_dest>, <reg_as_dest>} */

    /* Require 2 operands */
    {"mov", inst_mov, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE},
    {"cmp", inst_mov, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE},
    {"add", inst_mov, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE},
    {"sub", inst_mov, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE},
    {"lea", inst_mov, FALSE, TRUE, FALSE, FALSE, TRUE, TRUE},

    /* Require 1 operand */
    {"not", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"clr", inst_mov,  FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"inc", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"dec", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"jmp", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"bne", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"red", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"prn", inst_mov, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE},
    {"jsr", inst_mov, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},

    /* Without operands */
    {"rts", inst_mov, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {"stop", inst_mov, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    };

    asm_directive asm_all_directives[NUM_OF_DIR] = 
    {
    /* {<dir_name>, <sir_key>} */

    {"data", dir_data},
    {"string", dir_string},
    {"extern", dir_extern},
    {"entry", dir_entry},
    };

    /* Check if the line is a directive or an instruction and change the analyzed_line according to the result. */
    if (is_dir_or_inst(line) == DIR_ENUM_CODE)
        analyzed_line.analyzed_line_opt = directive;
    else
        analyzed_line.analyzed_line_opt = instruction;

    return analyzed_line;
}


int main()
{
    Analyzed_line result;
    char input_line[] = "bla";
    result = get_analyzed_line(input_line);
    return 0;
}