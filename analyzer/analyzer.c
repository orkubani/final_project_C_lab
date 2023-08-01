#include "analyzer.h"

asm_instruction asm_all_instructions[16] = 
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