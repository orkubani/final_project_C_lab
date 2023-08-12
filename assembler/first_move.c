#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/assembler_helper.h"

#define DEBUG

/* First move on the am_file. */
int first_move(FILE * am_file/*, Object_File * object_file*/, const char * am_filename)
{
    int j;
    int i;
    char line[MAX_LINE_LENGTH] = {0}; /* Initilize line */
    Analyzed_line analyzed_line;
    int dest_operand_i;
    int src_operand_i;
    int num_of_operands;
    int IC = 0;
    int DC = 0;
    Compiled_Line * data_section = NULL;
    Compiled_Line * code_section = NULL;
    Compiled_Line * current_compiled_line = NULL;
    Symbol * symbol = NULL;
    Symbol * temp_symbol = NULL;
    int line_index = 1;
    unsigned int inst_word = 0;

    #ifdef DEBUG
    char * output_filename = "/mnt/c/Or_Kubani_Openu_CS/2023B/maabada_20476/final_project_C_lab/tests/first_move/first_move_output.txt";
    FILE * output_file;
    output_file = fopen(output_filename, "w");
    #endif

    while (fgets(line, sizeof(line), am_file)) 
    {
        analyzed_line = get_analyzed_line(line);

        /* Check For Syntax Error */
        if (is_valid_analyzed_line(&analyzed_line) == FALSE)
        {
            printf("Error in line '%d'! %s\n", line_index, analyzed_line.syntax_error);
            line_index++;
            continue;
        }

        /* Add main label to the symbol table */
        if (strcmp(analyzed_line.label_name, "\0") != 0)
        {
            temp_symbol = get_symbol(symbol, analyzed_line.label_name);
            if (temp_symbol)
            {
                if (temp_symbol->symbol_opt == symbol_entry_def) 
                {
                    if (analyzed_line.analyzed_line_opt == directive)
                        symbol = insert_symbol_to_table(symbol, analyzed_line.label_name, line_index, symbol_entry_data);

                    else
                        symbol = insert_symbol_to_table(symbol, analyzed_line.label_name, line_index, symbol_entry_code);
                }

                else 
                {
                    printf("Redeclaration of label: '%s'!\n", analyzed_line.label_name);
                    assembler_error(line_index);
                }
            }

            else 
            {
                if (analyzed_line.analyzed_line_opt == directive)
                    symbol = insert_symbol_to_table(symbol, analyzed_line.label_name, line_index, symbol_local_data);

                else
                    symbol = insert_symbol_to_table(symbol, analyzed_line.label_name, line_index, symbol_local_code);
            }
        }

        /* Compile (First Move) Directive */
        if (analyzed_line.analyzed_line_opt == directive)
        {
            /* Add directive to the data section */
            data_section = insert_compiled_line_to_table(data_section, line_index);
            current_compiled_line = get_compiled_line(data_section, line_index);

            /* Compile String Directive */
            if (analyzed_line.dir_or_inst.directive.dir_opt == dir_string)
            {
                for (i = 0; analyzed_line.dir_or_inst.directive.dir_operand.string[i] != '\0'; i++)
                {
                    insert_word(current_compiled_line, analyzed_line.dir_or_inst.directive.dir_operand.string[i]);
                }
                
                insert_word(current_compiled_line, '\0');

                DC++;
                line_index++;
                continue;
            }

            /* Compile Data Directive */
            else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_data) 
            {
                for (i = 0; i < analyzed_line.dir_or_inst.directive.dir_operand.data.data_count; i++)
                {
                    insert_word(current_compiled_line, analyzed_line.dir_or_inst.directive.dir_operand.data.data[i]);
                }

                DC++;
                line_index++;
                continue;
            }

            /* entry def */
            else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_entry) 
            {
                temp_symbol = get_symbol(symbol, analyzed_line.dir_or_inst.directive.dir_operand.label_name);
                if (temp_symbol) 
                {
                    if (temp_symbol->symbol_opt == symbol_local_data) 
                    {
                        temp_symbol->symbol_opt = symbol_entry_data;
                    }

                    else if (temp_symbol->symbol_opt == symbol_local_code) 
                    {
                        temp_symbol->symbol_opt = symbol_entry_code;
                    }

                    else 
                    {
                        printf("The entry label '%s' is already defined not as entry!", analyzed_line.dir_or_inst.directive.dir_operand.label_name);
                        assembler_error(line_index);
                    }
                }

                symbol = insert_symbol_to_table(symbol, analyzed_line.dir_or_inst.directive.dir_operand.label_name,
                 line_index, symbol_entry_def);

                DC++;
                line_index++;
                continue;
            }

            /* extern def */
            else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_extern)
            {
                symbol = insert_symbol_to_table(symbol, analyzed_line.dir_or_inst.directive.dir_operand.label_name, 
                line_index, symbol_extern_def);

                DC++;
                line_index++;
                continue;
            }

            else 
            {
                line_index++;
                continue;
            }           
        }

        /* Compile (First Move) Instruction */
        else if (analyzed_line.analyzed_line_opt == instruction) 
        {
            
            /* Add Instruction to the code section */
            code_section = insert_compiled_line_to_table(code_section, line_index);
            
            /* Insert the inst word to the current compiled_line in the code_section. releavnt for all instructions. */
            inst_word = analyzed_line.dir_or_inst.instruction.inst_opt << OPCODE_INDENTATION;
            
            /* No Operands */
            if (analyzed_line.dir_or_inst.instruction.inst_operand_options[0] == operand_none && 
                analyzed_line.dir_or_inst.instruction.inst_operand_options[1] == operand_none)
            {
                /* Do nothing */
                current_compiled_line = get_compiled_line(code_section, line_index);
                insert_word(current_compiled_line, inst_word);
            } 

            /* Single Operand. */
            else if (analyzed_line.dir_or_inst.instruction.inst_operand_options[0] == operand_none || 
                     analyzed_line.dir_or_inst.instruction.inst_operand_options[1] == operand_none)
            {
                dest_operand_i = 0;
                num_of_operands = 1;
                inst_word |= analyzed_line.dir_or_inst.instruction.inst_operand_options[dest_operand_i] << DEST_INDENTATION;

                current_compiled_line = get_compiled_line(code_section, line_index);
                insert_word(current_compiled_line, inst_word);
            }

            /* Two Operands */
            else 
            {
                dest_operand_i = 1;
                src_operand_i = 0;
                num_of_operands = 2;
                inst_word |= analyzed_line.dir_or_inst.instruction.inst_operand_options[dest_operand_i] << DEST_INDENTATION;
                inst_word |= analyzed_line.dir_or_inst.instruction.inst_operand_options[src_operand_i] << SRC_INDENTATION;
                current_compiled_line = get_compiled_line(code_section, line_index);
                insert_word(current_compiled_line, inst_word);
            }     

            /* Add Extra Words. */
            set_inst_extra_words(analyzed_line, current_compiled_line, num_of_operands);
            IC++;
            line_index++;
            continue;
        }

        /* First Move failed */
        line_index++;
        return FALSE;
    } 

    #ifdef DEBUG

    fprintf(output_file, "\n############################ data_section ###########################\n");
    while (data_section != NULL) 
    {
        fprintf(output_file,"Line Index: '%d'\n",data_section->line_index);

        if (data_section->num_of_words > 0)
        {
            fprintf(output_file, "Num Of Words: '%d'\n",data_section->num_of_words);

            for(j = 0; j < data_section->num_of_words; j++)
            {
                print_file_decimal_to_binary(data_section->words[j], output_file);
            }   
        }
        fprintf(output_file, "\n");
        data_section = data_section->next_compiled_line;
    }

    fprintf(output_file, "\n############################ code_section ###########################\n");
    while (code_section != NULL) 
    {
        fprintf(output_file, "Line Index: '%d'\n",code_section->line_index);
        fprintf(output_file, "Num Of Words: '%d'\n",code_section->num_of_words);
        fprintf(output_file, "Missing Label 1 type: '%d'\n", code_section->missing_label_op_type[0]);
        fprintf(output_file, "Missing Label 1 name: '%s'\n", code_section->missing_label[0]);
        fprintf(output_file, "Missing Label 2 type: '%d'\n", code_section->missing_label_op_type[1]);
        fprintf(output_file, "Missing Label 2 name: '%s'\n", code_section->missing_label[1]);
        for(j = 0; j < code_section->num_of_words; j++)
        {
            print_file_decimal_to_binary(code_section->words[j], output_file);
        }

        fprintf(output_file, "\n");
        code_section = code_section->next_compiled_line;
    }

    fprintf(output_file, "\n############################ symbol_table ###########################\n");
    while(symbol != NULL)
    {
        fprintf(output_file, "Symbol name: '%s'\n", symbol->symbol_name);
        fprintf(output_file, "Symbol type: '%d'\n", symbol->symbol_opt);
        fprintf(output_file, "Symbol def_line: '%d'\n", symbol->def_line);
        fprintf(output_file, "Symbol address: '%d'\n", symbol->address);

        fprintf(output_file, "\n");
        symbol = symbol->next_symbol;
    }

    fclose(output_file);
    #endif

    /* Add here free symbol */
    free_compiled_line_table(data_section);
    free_compiled_line_table(code_section);
    return TRUE;
}