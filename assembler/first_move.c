#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>
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
    Compiled_Line * data_section = NULL;
    Compiled_Line * code_section = NULL;
    Compiled_Line * current_compiled_line = NULL;
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

        if (is_valid_analyzed_line(&analyzed_line) == FALSE)
        {
            printf("Error in line '%d'! %s\n", line_index, analyzed_line.syntax_error);
            line_index++;
            continue;
        }

        /* Handle Main Label Here */

        if (analyzed_line.analyzed_line_opt == directive)
        {
            data_section = insert_compiled_line_to_table(data_section, line_index);
            current_compiled_line = get_compiled_line(data_section, line_index);

            if (analyzed_line.dir_or_inst.directive.dir_opt == dir_string)
            {
                for (i = 0; analyzed_line.dir_or_inst.directive.dir_operand.string[i] != '\0'; i++)
                {
                    insert_word(current_compiled_line, analyzed_line.dir_or_inst.directive.dir_operand.string[i]);
                }
                
                insert_word(current_compiled_line, '\0');

                line_index++;
                continue;
            }

            else if (analyzed_line.dir_or_inst.directive.dir_opt == dir_data) 
            {
                for (i = 0; i < analyzed_line.dir_or_inst.directive.dir_operand.data.data_count; i++)
                {
                    insert_word(current_compiled_line, analyzed_line.dir_or_inst.directive.dir_operand.data.data[i]);
                }

                line_index++;
                continue;
            }

            /* Remember to change / delete */    
            else 
            {
                line_index++;
                continue;
            }           
        }

        else if (analyzed_line.analyzed_line_opt == instruction) 
        {
            code_section = insert_compiled_line_to_table(code_section, line_index);
            
            inst_word = analyzed_line.dir_or_inst.instruction.inst_opt << OPCODE_INDENTATION;
            
            if (analyzed_line.dir_or_inst.instruction.inst_operand_options[0] == operand_none && 
                analyzed_line.dir_or_inst.instruction.inst_operand_options[1] == operand_none)
            {
                /* Do nothing */
                current_compiled_line = get_compiled_line(code_section, line_index);
                insert_word(current_compiled_line, inst_word);
            } 

            else if (analyzed_line.dir_or_inst.instruction.inst_operand_options[0] == operand_none || 
                     analyzed_line.dir_or_inst.instruction.inst_operand_options[1] == operand_none)
            {
                dest_operand_i = 0;
                num_of_operands = 1;
                inst_word |= analyzed_line.dir_or_inst.instruction.inst_operand_options[dest_operand_i] << DEST_INDENTATION;

                current_compiled_line = get_compiled_line(code_section, line_index);
                insert_word(current_compiled_line, inst_word);
            }

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

            set_inst_extra_words(analyzed_line, current_compiled_line, num_of_operands);
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
        for(j = 0; j < code_section->num_of_words; j++)
        {
            print_file_decimal_to_binary(code_section->words[j], output_file);
        }

        fprintf(output_file, "\n");
        code_section = code_section->next_compiled_line;
    }

    fclose(output_file);
    #endif

    free_compiled_line_table(data_section);
    free_compiled_line_table(code_section);
    return TRUE;
}