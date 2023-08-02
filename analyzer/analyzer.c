#include "analyzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_syntax_error(char *line)
{
    /* return 1 if there is a syntax error */
    /* return 0 if there is no syntax error */ 
}

int is_dir_or_inst(char *line)
{
    int i;
    char clean_line[MAX_LINE_LENGTH];
    remove_white_spaces(line, clean_line);

    /* Option 1 when line is a directive. entry/extern */
    if (clean_line[0] == '.')
        return DIR_ENUM_CODE;
    
    /* Option 2 when line is a directive. label */
    for(i = 0; i < strlen(clean_line) - 1; i++)
    {
        if (clean_line[i] == ':' && clean_line[i + 1] == '.') 
        {
            return DIR_ENUM_CODE;
        }
    }

    return INST_ENUM_CODE;
}

Analyzed_line get_analyzed_line(char *line)
{
    Analyzed_line analyzed_line;

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

    if (is_syntax_error(line))
    {
        strcpy(analyzed_line.syntax_error, "Syntax Error was detected");
        return analyzed_line;
    }

    /* Check line type */
    if (is_dir_or_inst(line) == DIR_ENUM_CODE)
        analyzed_line.analyzed_line_opt = directive;
    else
        analyzed_line.analyzed_line_opt = instruction;

    return analyzed_line;
}


int main(int argc, char** argv)
{
    FILE * analyzer_input_test;
    Analyzed_line analyzed_line_result;
    char line[MAX_LINE_LENGTH];

    analyzer_input_test = fopen(argv[1], "r");
    if (analyzer_input_test == NULL) 
    {
        printf("Error opening the analyzer_input_test file.\n");
        return 0;
    }

    /* Analyze each line and perform the relevant action */
    while (fgets(line, MAX_LINE_LENGTH, analyzer_input_test) != NULL) 
    {
        analyzed_line_result = get_analyzed_line(line);
        printf("Line: %s", line);
        printf("Line Type (0 - directive | 1 instruction): %d\n\n", analyzed_line_result.analyzed_line_opt);
    }

    return 0;
}