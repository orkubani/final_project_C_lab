#include "analyzer.h"
#include "../helpers/analyzer_helper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struct that maps all the relevant Assembly Insructions. */
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

/* Struct that maps all the relevant Assembly Directives. */
static asm_directive asm_all_directives[NUM_OF_DIR] = 
{
    /* {<dir_name>, <sir_key>} */
    {".data", dir_data},
    {".string", dir_string},
    {".extern", dir_extern},
    {".entry", dir_entry},
};

/* Checks if there is a Label def in the line. If yes, set it to the Label's name, otherwise set to NULL.  */
void set_main_label(char *line, Analyzed_line *analyzed_line)
{
    int i;
    char label_name[MAX_LINE_LENGTH];
    char clean_line[MAX_LINE_LENGTH];

    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;

    remove_white_spaces(line, clean_line);

    /* Initialize label_name with null characters. */
    for (i = 0; i < MAX_LINE_LENGTH; i++) 
    {
        label_name[i] = '\0';
    }

    /* There is no label def in this line. */
    if (strchr(clean_line, ':') == NULL) 
    {
        /* Set the label_name to NULL. */
        strcpy(analyzed_line->label_name, label_name);
    }

    else 
    {
        /* Get the label name from the line */
        for (i = 0; clean_line[i] != ':'; i++) 
        {
            label_name[i] = clean_line[i];
        }

        label_name[i] = '\0';

        /* Set the label_name */
        strcpy(analyzed_line->label_name, label_name);
    }
}

/* Checks and sets if the current line is an Assembly instruction / directive. */
void set_dir_or_inst(char *line, Analyzed_line *analyzed_line)
{
    int i;
    char clean_line[MAX_LINE_LENGTH];

    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;

    remove_white_spaces(line, clean_line);

    /* Directive */
    for (i = 0; i < NUM_OF_DIR; i++) 
    {
        if (strstr(clean_line, asm_all_directives[i].dir_name) != NULL) 
        {
            analyzed_line->analyzed_line_opt = directive;
            analyzed_line->dir_or_inst.directive.dir_opt = asm_all_directives[i].dir_key;
            return;
        }
    }

    /* Instruction */
    for (i = 0; i < NUM_OF_INST; i++)
    {
        if (strstr(clean_line, asm_all_instructions[i].inst_name) != NULL)
        {
            analyzed_line->analyzed_line_opt = instruction;
            analyzed_line->dir_or_inst.instruction.inst_opt = asm_all_instructions[i].inst_key;
            return;
        }
    }

    /* Not dir or inst. */
    sprintf(analyzed_line->syntax_error, "The current line is not a valid Assembly instruction/directive!");
    return;
}

/* Set the label name of a '.entry' / '.extern' Assembly directive. */
void set_ent_ext_label(char * line, Analyzed_line *analyzed_line)
{
    char clean_line[MAX_LINE_LENGTH];
    char * label_name;

    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;
    
    remove_white_spaces(line, clean_line);

    /* Get extern label name */
    if (analyzed_line->dir_or_inst.directive.dir_opt == dir_extern)
    {
        label_name = strstr(clean_line, DOT_EXT_AS_STRING);

        if (label_name == NULL)
            return;
            
        label_name += strlen(DOT_EXT_AS_STRING); /* Skip the '.extern' string */
        strcpy(analyzed_line->dir_or_inst.directive.dir_operand.label_name, label_name);
        return;
    }

    /* Get entry label name */     
    else if(analyzed_line->dir_or_inst.directive.dir_opt == dir_entry)
    {
        label_name = strstr(clean_line, DOT_ENT_AS_STRING);

        if (label_name == NULL)
            return;
        
        label_name += strlen(DOT_ENT_AS_STRING); /* Skip the '.entry' string */
        strcpy(analyzed_line->dir_or_inst.directive.dir_operand.label_name, label_name);
        return;
    }

    return;
}

/* Set the string of a '.string' Assembly directive. */
void set_dir_string(char * line, Analyzed_line *analyzed_line)
{
    char clean_line[MAX_LINE_LENGTH];
    char * string_content = NULL;

    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;

    remove_white_spaces(line, clean_line);

    string_content = strchr(clean_line, '\"');
    if (string_content == NULL)
    {
        sprintf(analyzed_line->syntax_error, "Invalid '.string' content syntax! Quotations are missing!");
        return;
    }

    string_content = remove_str_quotations(string_content);
    if (string_content[0] == '\0')
    {
        sprintf(analyzed_line->syntax_error, "Invalid '.string' content syntax! The closer quotation is missing!");
        return;
    }

    strcpy(analyzed_line->dir_or_inst.directive.dir_operand.string, string_content);
    return;
}

/* Set the data of a '.data' Assembly directive. */
void set_dir_data(char *line, Analyzed_line *analyzed_line)
{
    int i = 0;
    char clean_line[MAX_LINE_LENGTH];
    char * data_content_as_string;
    long int num;
    int num_conversion_result;

    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;

    remove_white_spaces(line, clean_line);

    data_content_as_string = strrchr(clean_line, ':');
    data_content_as_string += (strlen(DOT_DATA_AS_STRING) + 1); /* Skip the last 'a' */

    while (sscanf(data_content_as_string, "%ld%n", &num, &num_conversion_result) == 1) 
    {
        /* Catch floats */
        if (num_conversion_result == 0 || data_content_as_string[num_conversion_result] != ',')
        {
            if (data_content_as_string[num_conversion_result] != '\0')
            {
                sprintf(analyzed_line->syntax_error, "Invalid data content! .data content must be an integer!");
                return;
            }
        }

        data_content_as_string = strchr(data_content_as_string, ',');
        analyzed_line->dir_or_inst.directive.dir_operand.data.data[i] = num;
        i++;
        analyzed_line->dir_or_inst.directive.dir_operand.data.data_count = i;

        if (data_content_as_string == NULL)
            break;
        
        data_content_as_string += 1;
    }

    /* Catch Strings / Chars */
    if (data_content_as_string != NULL)
    {
        sprintf(analyzed_line->syntax_error, "Invalid data content! .data content must be an integer!");
        return;
    }
}

/* Set an Assembly directive according to the directive type. */
void set_directive(char * line, Analyzed_line *analyzed_line) 
{
    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;

    if (analyzed_line->dir_or_inst.directive.dir_opt == dir_entry || analyzed_line->dir_or_inst.directive.dir_opt == dir_extern)
    {
        set_ent_ext_label(line, analyzed_line);
        return;
    }
        
    else if (analyzed_line->dir_or_inst.directive.dir_opt == dir_string)
    {
        set_dir_string(line, analyzed_line);
        return;
    }
        
    else if (analyzed_line->dir_or_inst.directive.dir_opt == dir_data)
    {
        set_dir_data(line, analyzed_line);
        return;
    }

    return;
}

/* Get the instruction name from the table based on the instruction enum code. */
const char * get_inst_name(int inst_enum_code)
{
    int i;
    
    for (i = 0; i < NUM_OF_INST; i++)
    {
        if (inst_enum_code == asm_all_instructions[i].inst_key) 
        {
            return asm_all_instructions[i].inst_name;
        }
    }

    /* Error */
    return NULL;
}

/* Get the inst_content - the data that comes after the opcode. */
char * get_inst_content(const char * inst_name, char * clean_line)
{
    char * inst_content;
    int inst_len = 0;

    inst_content = strpbrk(clean_line, inst_name);
    inst_len = strlen(inst_name);
    return inst_content += inst_len;
}

/* Get the numbers of operands of the current instruction. */
int get_num_inst_operands(int inst_enum_code)
{
    int i;
    int src = 0;
    int dest = 0;

    for (i=0; i < NUM_OF_INST; i++)
    {
        if (inst_enum_code == asm_all_instructions[i].inst_key) 
        {
            /* Checks if at least one of the Addressing Modes is allowed as src. */
            if (asm_all_instructions[i].immed_as_src == TRUE || 
                asm_all_instructions[i].label_as_src == TRUE || 
                asm_all_instructions[i].reg_as_src == TRUE) 
                src = 1;
            
            /* Checks if at least one of the Addressing Modes is allowed as dest. */
            if (asm_all_instructions[i].immed_as_dest == TRUE || 
                asm_all_instructions[i].label_as_dest == TRUE || 
                asm_all_instructions[i].reg_as_dest == TRUE) 
                dest = 1;

            return src + dest;
        }
    }

    return -1;
}

/* Set instruction operand - Register / Const Number / Label. */
void set_inst_operand(char * inst_operand, Analyzed_line *analyzed_line, int operand_i) /* Before Error System */
{
    int reg_num = -1;

    if (is_valid_analyzed_line(analyzed_line) == FALSE)
        return; 
    
    /* Set Register */
    if (*inst_operand == '@')
    {
        if(*(inst_operand + 1) == 'r')
        {
            reg_num = str_to_int(inst_operand + 2);

            if (reg_num >= MIN_REG_NUM && reg_num <= MAX_REG_NUM)
            {
                analyzed_line->dir_or_inst.instruction.inst_operand_options[operand_i] = operand_register;
                analyzed_line->dir_or_inst.instruction.inst_operands[operand_i].register_number = get_reg_num(inst_operand);
                return;
            }

            sprintf(analyzed_line->syntax_error, "Invalid register number! '%d'", reg_num);
            return;
        }
        return;
    } 

    /* Set Const Number */
    else if(is_integer(inst_operand))
    {
        analyzed_line->dir_or_inst.instruction.inst_operand_options[operand_i] = operand_const_number;
        analyzed_line->dir_or_inst.instruction.inst_operands[operand_i].const_number = str_to_int(inst_operand);
        return;
    }

    /* Set Label */
    analyzed_line->dir_or_inst.instruction.inst_operand_options[operand_i] = operand_label;
    strcpy(analyzed_line->dir_or_inst.instruction.inst_operands[operand_i].label, inst_operand);
    return; 
}

/* Set an Assembly Instruction and related data regarding the instruction. */
void set_instruction(char *line, Analyzed_line *analyzed_line)
{
    int i;
    const char* inst_name;
    char * inst_content;
    int num_of_operands;
    char operands[TWO_OPERANDS][MAX_OPERAND_LENGTH];
    char clean_line[MAX_LINE_LENGTH];
    int first_op = 0;
    int second_op = 1;

    if (is_valid_analyzed_line(analyzed_line) == FALSE) 
        return;

    remove_white_spaces(line, clean_line);

    /* Initilize first_operand & second_operand to be NULL */
    memset(operands, 0, sizeof(operands));

    /* Get inst data */
    inst_name = get_inst_name(analyzed_line->dir_or_inst.instruction.inst_opt);
    if (inst_name == NULL)
    {
        sprintf(analyzed_line->syntax_error, "Can't find instruction name for inst_opt: '%d'", analyzed_line->dir_or_inst.instruction.inst_opt);
        return;
    }

    inst_content = get_inst_content(inst_name, clean_line);
    num_of_operands = get_num_inst_operands(analyzed_line->dir_or_inst.instruction.inst_opt);

    /* Set instruction with two operands */
    if (num_of_operands == TWO_OPERANDS)
    {
        
        if(strlen(inst_content) == 0)
        {
            sprintf(analyzed_line->syntax_error, "Invalid body for inst: '%s'! There body is empty!", inst_name);
            return;
        }
        
        if (strchr(inst_content, ',') == NULL)
        {
            sprintf(analyzed_line->syntax_error, "Invalid body for inst: '%s'! There are no 2 operands!", inst_name);
            return;
        }

        split_operands(inst_content, operands[first_op], operands[second_op]);

        for (i = 0; i < num_of_operands; i++)
        {
            set_inst_operand(operands[i], analyzed_line, i);
        }
        return;
    }

    /* Set instruction with a single operand */
    else if (num_of_operands == SINGLE_OPERAND)
    {

        if(strlen(inst_content) == 0)
        {
            sprintf(analyzed_line->syntax_error, "Invalid body for inst: '%s'! There body is empty!", inst_name);
            return;
        }

        if (strchr(inst_content, ',') != NULL)
        {
            sprintf(analyzed_line->syntax_error, "Invalid body for inst: '%s'! There are more than 1 operands!", inst_name);
            return;
        }

        strcpy(operands[first_op], inst_content);
        set_inst_operand(operands[first_op],analyzed_line, first_op);
        analyzed_line->dir_or_inst.instruction.inst_operand_options[second_op] = operand_none;
        return;
    }

    /* Set instruction with zero operands */
    else if (num_of_operands == ZERO_OPERANDS)
    {
        if(strlen(inst_content) != 0)
        {
            sprintf(analyzed_line->syntax_error, "Invalid body for inst: '%s'! There body is not empty!", inst_name);
            return;
        }

        analyzed_line->dir_or_inst.instruction.inst_operand_options[first_op] = operand_none;
        analyzed_line->dir_or_inst.instruction.inst_operand_options[second_op] = operand_none;
        return;
    }


    sprintf(analyzed_line->syntax_error, "Invalid number of operands!");    
    return;
}

/* Analayzes and "Brakes" a line into a structure of Assembly directive / instruction. */
Analyzed_line get_analyzed_line(char *line) /* Before Error System */
{
    /* Create 'analyzed_line' obj and remove white spaces. */
    Analyzed_line analyzed_line;

    /* Set main fields of the Analyzed_line obj */
    set_main_label(line, &analyzed_line);
    set_dir_or_inst(line, &analyzed_line);

    /* Set Assembly Directive */
    if (analyzed_line.analyzed_line_opt == directive)
    {
        set_directive(line, &analyzed_line);
    }
    
    /* Set Assembly Instruction */
    else if(analyzed_line.analyzed_line_opt == instruction)
    {
        set_instruction(line, &analyzed_line);
    }

    return analyzed_line;
}