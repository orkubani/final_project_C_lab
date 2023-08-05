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
    {"cmp", inst_cmp, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE},
    {"add", inst_add, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE},
    {"sub", inst_sub, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE},
    {"lea", inst_lea, FALSE, TRUE, FALSE, FALSE, TRUE, TRUE},

    /* Require 1 operand */
    {"not", inst_not, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"clr", inst_clr,  FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"inc", inst_inc, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"dec", inst_dec, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"jmp", inst_jmp, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"bne", inst_bne, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"red", inst_red, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},
    {"prn", inst_prn, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE},
    {"jsr", inst_jsr, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE},

    /* Without operands */
    {"rts", inst_rts, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {"stop", inst_stop, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
};

static asm_directive asm_all_directives[NUM_OF_DIR] = 
{
    /* {<dir_name>, <sir_key>} */
    {".data", dir_data},
    {".string", dir_string},
    {".extern", dir_extern},
    {".entry", dir_entry},
};

int get_main_label(char *clean_line, Analyzed_line *analyzed_line) /* Before Opti | Before Error System */
{
    int i;
    char label_name[MAX_LINE_LENGTH];

    /* Initialize label_name with null characters. */
    for (i = 0; i < MAX_LINE_LENGTH; i++) 
    {
        label_name[i] = '\0';
    }

    /* There is no label def in this line. */
    if (strchr(clean_line, ':') == NULL) 
    {
        strcpy(analyzed_line->label_name, label_name);
        return 0;
    }

    /* Get the label name from the line */
    for (i = 0; clean_line[i] != ':'; i++) 
    {
        label_name[i] = clean_line[i];
    }

    label_name[i] = '\0';
    strcpy(analyzed_line->label_name, label_name);
    return 1;
}

int is_dir_or_inst(char *clean_line, Analyzed_line *analyzed_line) /* Before Opti | Before Error System | Before update of dir type */
{
    int i;

    /* Option 1 when line is a directive. (entry/extern) */
    if (clean_line[0] == '.')
    {
        analyzed_line->analyzed_line_opt = directive;
        return directive;
    }
        
    /* Option 2 when line is a directive. (label) */
    for(i = 0; i < strlen(clean_line) - 1; i++)
    {
        if (clean_line[i] == ':' && clean_line[i + 1] == '.') 
        {
            analyzed_line->analyzed_line_opt = directive;
            return directive;
        }
    }

    for (i = 0; i < NUM_OF_INST; i++)
    {
        if (strstr(clean_line, asm_all_instructions[i].inst_name) != NULL)
        {
            analyzed_line->analyzed_line_opt = instruction;
            analyzed_line->dir_or_inst.instruction.inst_opt = asm_all_instructions[i].inst_key;
            return instruction;
        }
    }

    /* Not dir or inst */
    analyzed_line->analyzed_line_opt = -1;
    return 0;
}

int get_dir_type(char * clean_line, Analyzed_line *analyzed_line) /* Before Opti | Before Error System */
{
    char * str_or_data;
    const char * delimiter = ":.";
    
    /* enrty/extern */
    if (clean_line[0] == '.')
    {
        /* entry */
        if(strncmp(clean_line, DOT_ENT_AS_STRING, DOT_ENTRY_LEN) == 0)
        {
            analyzed_line->dir_or_inst.directive.dir_opt = dir_entry;
            return 1;
        }
                    
        /* extern */        
        else if(strncmp(clean_line, DOT_EXT_AS_STRING, DOT_EXTERN_LEN) == 0)
        {
            analyzed_line->dir_or_inst.directive.dir_opt = dir_extern;
            return 1;
        }
    }

    /* Get data/string */
    str_or_data = strstr(clean_line, delimiter);
    if (str_or_data == NULL)
        return 0;
    str_or_data += strlen(delimiter) - 1; /* Get the string after the ':' */
    
    /* string */
    if (strncmp(str_or_data, DOT_STR_AS_STRING, DOT_STR_LEN) == 0)
    {
        analyzed_line->dir_or_inst.directive.dir_opt = dir_string;
        return 1;
    }

    /* data */
    else if (strncmp(str_or_data, DOT_DATA_AS_STRING, DOT_DATA_LEN) == 0)
    {
        analyzed_line->dir_or_inst.directive.dir_opt = dir_data;
        return 1;
    }
    
    return 0;
}

char * get_ent_ext_label(char * line, int dir_opt, asm_directive asm_all_directives[NUM_OF_DIR]) /* Before Opti | Before Error System */
{
    char clean_line[MAX_LINE_LENGTH];
    char * label_name;
    remove_white_spaces(line, clean_line);

    /* Get extern label name */
    if (dir_opt == dir_extern)
    {
        label_name = strstr(clean_line, DOT_EXT_AS_STRING);

        if (label_name == NULL)
            return NULL;
    
        label_name += strlen(DOT_EXT_AS_STRING);

        return label_name;
    }

    /* Get entry label name */     
    else if(dir_opt == dir_entry)
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

char * get_dir_string(char * line) /* Before Opti | Before Error System */
{
    char clean_line[MAX_LINE_LENGTH];
    char * string_content;
    remove_white_spaces(line, clean_line);

    string_content = strchr(clean_line, '\"');
    string_content = remove_str_quotations(string_content);

    return string_content;
}

void get_dir_data(char *line, Analyzed_line *analyzed_line) /* Before Opti | Before Error System */
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

const char * get_inst_name(int inst_enum_code) /* Before Opti | Before Error System */
{
    int i;
    
    for (i = 0; i < NUM_OF_INST; i++)
    {
        if (inst_enum_code == asm_all_instructions[i].inst_key) 
        {
            return asm_all_instructions[i].inst_name;
        }
    }

    return NULL;
}

int get_num_inst_operands(int inst_enum_code) /* Before Opti | Before Error System */
{
    int i;
    int src = 0;
    int dest = 0;

    for (i=0; i < NUM_OF_INST; i++)
    {
        if (inst_enum_code == asm_all_instructions[i].inst_key) 
        {
            if (asm_all_instructions[i].immed_as_src == TRUE || 
                asm_all_instructions[i].label_as_src == TRUE || 
                asm_all_instructions[i].reg_as_src == TRUE) 
                src = 1;
            
            if (asm_all_instructions[i].immed_as_dest == TRUE || 
                asm_all_instructions[i].label_as_dest == TRUE || 
                asm_all_instructions[i].reg_as_dest == TRUE) 
                dest = 1;

            return src + dest;
        }
    }

    return -1;
}

int get_inst_operands(char *clean_line, Analyzed_line *analyzed_line, int inst_opt) /* Before Opti | Before Error System */
{
    char * inst_content;
    const char* inst_name;
    int num_of_operands;
    char first_operand[MAX_OPERAND_LENGTH];
    char second_operand[MAX_OPERAND_LENGTH];
    int inst_len = 0;

    /* Initilize first_operand & second_operand to be NULL */
    memset(first_operand, 0, sizeof(first_operand));
    memset(second_operand, 0, sizeof(second_operand));

    inst_name = get_inst_name(inst_opt);
    inst_content = strpbrk(clean_line, inst_name);
    inst_len = strlen(inst_name);
    inst_content += inst_len;
    num_of_operands = get_num_inst_operands(inst_opt);

    if (num_of_operands == 2)
    {
        split_operands(inst_content, first_operand, second_operand);
    }

    else if (num_of_operands == 1)
    {
        strcpy(first_operand, inst_content);
    }

    else if (num_of_operands == 0)
    {
        analyzed_line->dir_or_inst.instruction.inst_operand_options[0] = operand_none;
        analyzed_line->dir_or_inst.instruction.inst_operand_options[1] = operand_none;
        return 1;
    }
        
    return 0;
}

Analyzed_line get_analyzed_line(char *line)
{
    Analyzed_line analyzed_line;
    char clean_line[MAX_LINE_LENGTH];
    remove_white_spaces(line, clean_line);

    get_main_label(clean_line, &analyzed_line);
    is_dir_or_inst(clean_line, &analyzed_line);

    if (analyzed_line.analyzed_line_opt == directive)
    {
        get_dir_type(clean_line, &analyzed_line);

        if (analyzed_line.dir_or_inst.directive.dir_opt == dir_entry || analyzed_line.dir_or_inst.directive.dir_opt == dir_extern)
            analyzed_line.dir_or_inst.directive.dir_operand.label_name = get_ent_ext_label(line, analyzed_line.dir_or_inst.directive.dir_opt == dir_entry, asm_all_directives);
        
        else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_string)
            analyzed_line.dir_or_inst.directive.dir_operand.string = get_dir_string(line);

        else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_data)
         get_dir_data(line, &analyzed_line);
    }
        
    else if(analyzed_line.analyzed_line_opt == instruction)
    {
        get_inst_operands(clean_line, &analyzed_line, analyzed_line.dir_or_inst.instruction.inst_opt);
    }

    return analyzed_line;
}