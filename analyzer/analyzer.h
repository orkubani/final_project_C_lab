#ifndef ANALYZER_H
#define ANALYZER_H

#include "../helpers/utils.h"

#define NUM_OF_INST 16
#define NUM_OF_DIR 4
#define MAX_SYTX_ERR_LENGTH 200

#define DIR_ENUM_CODE 0
#define INST_ENUM_CODE 1

typedef struct Analyzed_line
{
    char syntax_error[MAX_SYTX_ERR_LENGTH];
    char label_name[MAX_LABEL_LENGTH]; 

    /* Only one of the following can be the line type. Blank and Comment lines are in the preprocessor responsibility. */
    enum
    {
        directive,
        instruction
    }analyzed_line_opt;

    union
    {
        struct /* Directive */
        {
            enum /* Four kinds of directive */
            {
                dir_extern,
                dir_entry,
                dir_string,
                dir_data

            }dir_opt;

            union
            {
                char * label_name; /* .entry or .extern */
                char * string; /* .string */
                struct /* .data */
                {
                    int data[MAX_LINE_LENGTH];
                    int data_count;
                }data;

            }dir_operand;

        }directive; /* End of Directive */

        struct /* Instruction */
        {
            enum /* 16 opcodes */
            {
                /* Require 2 operands */
                inst_mov,
                inst_cmp,
                inst_add,
                inst_sub,
                inst_lea,

                /* Require 1 operand */
                inst_not,
                inst_clr,
                inst_inc,
                inst_dec,
                inst_jmp,
                inst_bne,
                inst_red,
                inst_prn,
                inst_jsr,

                /* Without operands */
                inst_rts,
                inst_stop

            }inst_opt;

            enum /* Addressing mode */
            {
                operand_none = 0,
                operand_const_number = 1,
                operand_label = 3,
                operand_register = 5

            }inst_operand_options;

            union
            {
                int const_number;
                int register_number;
                char * label;

            }inst_operands[2]; /* 2 for source and dest */

        }instruction; /* End of Instruction */

    }dir_or_inst;
}Analyzed_line;

typedef struct asm_instruction
{
    const char *inst_name;
    int inst_key;

    /* Allowed addressing mode of the src operand */
    int immed_as_src;
    int label_as_src;
    int reg_as_src;

    /* Allowed addressing mode of the dest operand */
    int immed_as_dest;
    int label_as_dest;
    int reg_as_dest;

}asm_instruction;

typedef struct asm_directive
{
    const char * dir_name;
    int dir_key;

}asm_directive;

int is_syntax_error(char *line);
int is_dir_or_inst(char *line);
int get_dir_enum_key(asm_directive asm_all_directives[NUM_OF_DIR], char * dir_name);
int get_dir_type(char * line, asm_directive asm_all_directives[NUM_OF_DIR]);
Analyzed_line get_analyzed_line(char *line);

#endif /* ANALYZER_H */