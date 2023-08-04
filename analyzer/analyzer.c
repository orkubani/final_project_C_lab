#include "analyzer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static asm_instruction asm_all_instructions[NUM_OF_INST] =
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

static asm_directive asm_all_directives[NUM_OF_DIR] = 
{
    /* {<dir_name>, <sir_key>} */
    {".data", dir_data},
    {".string", dir_string},
    {".extern", dir_extern},
    {".entry", dir_entry},
};

int get_main_label(char *line, Analyzed_line *analyzed_line)
{
    int i;
    char clean_line[MAX_LINE_LENGTH];
    char label_name[MAX_LINE_LENGTH];
    remove_white_spaces(line, clean_line);

    if (strchr(clean_line, ':') != NULL) 
    {
        for (i = 0; clean_line[i] != ':'; i++) 
        {
            label_name[i] = clean_line[i];
        }

        label_name[i] = '\0';
        strcpy(analyzed_line->label_name, label_name);
        return 1;
    }

    return 0;
}

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
    char clean_line[MAX_LINE_LENGTH];
    char * string_content;
    remove_white_spaces(line, clean_line);

    string_content = strchr(clean_line, '\"');
    string_content = remove_str_quotations(string_content);

    return string_content;
}

void get_dir_data(char *line, Analyzed_line *analyzed_line) /* Checkd, can be splited to helper */
{
    int i = 0;
    char clean_line[MAX_LINE_LENGTH];
    char * data_content_as_string;
    long int num;

    remove_white_spaces(line, clean_line);

    data_content_as_string = strrchr(clean_line, 'a');
    data_content_as_string += 1; /* Skip the last 'a' */

    while (sscanf(data_content_as_string, "%ld", &num) == 1) 
    {
        data_content_as_string = strchr(data_content_as_string, ',');
        analyzed_line->dir_or_inst.directive.dir_operand.data.data[i] = num;
        i++;
        analyzed_line->dir_or_inst.directive.dir_operand.data.data_count = i;

        if (data_content_as_string == NULL)
            break;
        
        data_content_as_string += 1;
    }
}

Analyzed_line get_analyzed_line(char *line)
{
    Analyzed_line analyzed_line;

    get_main_label(line, &analyzed_line);

    if (is_dir_or_inst(line) == DIR_ENUM_CODE)
    {
        analyzed_line.analyzed_line_opt = directive;
        analyzed_line.dir_or_inst.directive.dir_opt = get_dir_type(line, asm_all_directives);

        if (analyzed_line.dir_or_inst.directive.dir_opt == dir_entry || analyzed_line.dir_or_inst.directive.dir_opt == dir_extern)
            analyzed_line.dir_or_inst.directive.dir_operand.label_name = get_ent_ext_label(line, analyzed_line.dir_or_inst.directive.dir_opt == dir_entry, asm_all_directives);
        
        else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_string)
            analyzed_line.dir_or_inst.directive.dir_operand.string = get_dir_string(line);

        else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_data)
         get_dir_data(line, &analyzed_line);
    }
        
    else
        analyzed_line.analyzed_line_opt = instruction;

    return analyzed_line;
}