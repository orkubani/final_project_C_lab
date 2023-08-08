#ifndef ANALYZER_H
#define ANALYZER_H

#include "../helpers/utils.h"

#define NUM_OF_INST 16
#define NUM_OF_DIR 4
#define MAX_SYTX_ERR_LENGTH 200

#define TWO_OPERANDS 2
#define SINGLE_OPERAND 1
#define ZERO_OPERANDS 0

#define DOT_ENT_AS_STRING ".entry"
#define DOT_EXT_AS_STRING ".extern"
#define DOT_STR_AS_STRING ".string"
#define DOT_DATA_AS_STRING ".data"

#define DOT_STR_LEN 7
#define DOT_DATA_LEN 5
#define DOT_ENTRY_LEN 6
#define DOT_EXTERN_LEN 7

/* Ast that defines a Direcitve / Instruction in Assembly */
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

            }inst_operand_options[2];

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

/**
 * @brief Checks if there is a Label def in the line. If yes, set it to the Label's name, otherwise set to NULL.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_main_label(char *line, Analyzed_line *analyzed_line);

/**
 * @brief Checks and sets if the current line is an Assembly instruction / directive.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_dir_or_inst(char *line, Analyzed_line *analyzed_line);

/**
 * @brief Set the label name of a '.entry' / '.extern' Assembly directive.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_ent_ext_label(char * line, Analyzed_line *analyzed_line);

/**
 * @brief Set the string of a '.string' Assembly directive.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_dir_string(char * line, Analyzed_line *analyzed_line);

/**
 * @brief Set the data of a '.data' Assembly directive.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_dir_data(char *line, Analyzed_line *analyzed_line);

/**
 * @brief Set an Assembly directive according to the directive type.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_directive(char * line, Analyzed_line *analyzed_line);

/**
 * @brief Get the instruction name from the table based on the instruction enum code.
 *
 * @param inst_enum_code instruction enum code.
 * @return Pointer to a const string of the instruction name.
 */
const char * get_inst_name(int inst_enum_code);

/**
 * @brief 
 *
 * @param 
 * @param 
 */
char * get_inst_content(const char * inst_name, char * clean_line);

/**
 * @brief 
 *
 * @param 
 * @param 
 */
int get_num_inst_operands(int inst_enum_code);

/**
 * @brief 
 *
 * @param 
 * @param 
 */
void set_inst_operand(char * inst_operand, Analyzed_line *analyzed_line, int operand_i);

/**
 * @brief Set an Assembly Instruction and related data regarding the instruction.
 *
 * @param line The input line to check.
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 */
void set_instruction(char *line, Analyzed_line *analyzed_line);

/**
 * @brief 
 *
 * @param 
 * @param 
 */
Analyzed_line get_analyzed_line(char *line);

#endif /* ANALYZER_H */