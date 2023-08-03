#include "analyzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_dir_or_inst(char *line) /* Checked */
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

int get_dir_enum_key(asm_directive asm_all_directives[NUM_OF_DIR], char * dir_name) /* Checked */
{
    int i;

    for (i = 0; i < NUM_OF_DIR; i++) 
    {
        if (strcmp(asm_all_directives[i].dir_name, dir_name) == 0) 
        {
            return asm_all_directives[i].dir_key;
        }
    }

    return INVALID_VALUE;
}

int get_dir_type(char * line, asm_directive asm_all_directives[NUM_OF_DIR]) /* Checked */
{
    char clean_line[MAX_LINE_LENGTH];
    char * str_or_data;
    const char * delimiter = ":.";
    
    remove_white_spaces(line, clean_line);

    if (clean_line[0] == '.')
    {
        /* entry */
        if(strncmp(clean_line, DOT_ENT_AS_STRING, DOT_ENTRY_LEN) == 0)
            return get_dir_enum_key(asm_all_directives, DOT_ENT_AS_STRING);
        
        /* extern */        
        else if(strncmp(clean_line, DOT_EXT_AS_STRING, DOT_EXTERN_LEN) == 0)
            return get_dir_enum_key(asm_all_directives, DOT_EXT_AS_STRING);;
    }

    str_or_data = strstr(clean_line, delimiter);

    if (str_or_data == NULL)
        return INVALID_VALUE;
    
    str_or_data += strlen(delimiter) - 1; /* Get the string after the ':' */
    
    /* string */
    if (strncmp(str_or_data, DOT_STR_AS_STRING, DOT_STR_LEN) == 0)
        return get_dir_enum_key(asm_all_directives, DOT_STR_AS_STRING);

    /* data */
    else if (strncmp(str_or_data, DOT_DATA_AS_STRING, DOT_DATA_LEN) == 0)
        return get_dir_enum_key(asm_all_directives, DOT_DATA_AS_STRING);
    
    /* Invalid directive type */
    return INVALID_VALUE;
}

char * get_ent_ext_label(char * line, int dir_opt, asm_directive asm_all_directives[NUM_OF_DIR]) /* Checked */
{
    char clean_line[MAX_LINE_LENGTH];
    char * label_name;
    remove_white_spaces(line, clean_line);

    /* Get entry label name */
    if (dir_opt == get_dir_enum_key(asm_all_directives, DOT_EXT_AS_STRING))
    {
        label_name = strstr(clean_line, DOT_EXT_AS_STRING);

        if (label_name == NULL)
            return NULL;
    
        label_name += strlen(DOT_EXT_AS_STRING);

        return label_name;
    }

    /* Get extern label name */     
    else if(dir_opt == get_dir_enum_key(asm_all_directives, DOT_ENT_AS_STRING))
    {
        label_name = strstr(clean_line, DOT_ENT_AS_STRING);

        if (label_name == NULL)
            return NULL;
    
        label_name += strlen(DOT_ENT_AS_STRING);

        return label_name;
    }

    /* Error */
    return NULL;
}

char * get_dir_string(char * line) /* Checked */
{
    int i;
    char clean_line[MAX_LINE_LENGTH];
    char * string_content;
    remove_white_spaces(line, clean_line);

    string_content = strchr(clean_line, '\"');

    if (string_content == NULL)
        return NULL;

    string_content += 1;

    for(i = 0; string_content[i] != '\0'; i++)
    {
        if (string_content[i] == '\"')
        {
            string_content[i] = '\0';
        }
    }

    return string_content;
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

    {".data", dir_data},
    {".string", dir_string},
    {".extern", dir_extern},
    {".entry", dir_entry},
    };

    if (is_dir_or_inst(line) == DIR_ENUM_CODE)
    {
        analyzed_line.analyzed_line_opt = directive;
        analyzed_line.dir_or_inst.directive.dir_opt = get_dir_type(line, asm_all_directives);

        if (analyzed_line.dir_or_inst.directive.dir_opt == dir_entry || analyzed_line.dir_or_inst.directive.dir_opt == dir_extern)
            analyzed_line.dir_or_inst.directive.dir_operand.label_name = get_ent_ext_label(line, analyzed_line.dir_or_inst.directive.dir_opt == dir_entry, asm_all_directives);
        
        else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_string)
            analyzed_line.dir_or_inst.directive.dir_operand.string = get_dir_string(line);
    }
        
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
        if (analyzed_line_result.analyzed_line_opt == 0)
        {
            printf("Line: %s", line);
            printf("Line Type: %d\n", analyzed_line_result.analyzed_line_opt);
            printf("Dir type: %d\n",analyzed_line_result.dir_or_inst.directive.dir_opt);
            if (analyzed_line_result.dir_or_inst.directive.dir_opt == 0 || analyzed_line_result.dir_or_inst.directive.dir_opt == 1) 
            {
                printf("Label name: %s\n",analyzed_line_result.dir_or_inst.directive.dir_operand.label_name);
            }
            printf("\n");
        } 
    }

    return 0;
}