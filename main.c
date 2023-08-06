#include "preprocessor/preprocessor.h"
#include "analyzer/analyzer.h"
#include <stdio.h>


int main(int argc, char **argv)
{
    int i;
    int j;
    char * am_filename;
    FILE * am_file;
    FILE * analyzer_tester_output;
    char line[MAX_LINE_LENGTH];
    Analyzed_line analyzed_line_result;

    for(i = 1; i < argc; i++)
    {
        am_filename = process_as_file(argv[i]);
        
        am_file = fopen(am_filename, "r");
        if (am_file == NULL) 
        {
            printf("Error opening the analyzer_input_test file.\n");
            return 0;
        }

        analyzer_tester_output = fopen("/mnt/c/Or_Kubani_Openu_CS/2023B/maabada_20476/final_project_C_lab/tests/analyzer/analyzer_output.txt", "w");
        if (analyzer_tester_output == NULL) 
        {
            printf("Error opening the analyzer_tester_output file.\n");
            return 0;
        }

        /* Analyze each line and perform the relevant action */
        while (fgets(line, MAX_LINE_LENGTH, am_file) != NULL) 
        {
            analyzed_line_result = get_analyzed_line(line);
            fprintf(analyzer_tester_output,"Line: %s", line);
            fprintf(analyzer_tester_output, "Main Label: '%s'\n", analyzed_line_result.label_name);

            /* Print dir */
            if (analyzed_line_result.analyzed_line_opt == directive)
            {
                fprintf(analyzer_tester_output, "Line Type: 'directive'\n");

                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_entry)
                {
                    fprintf(analyzer_tester_output, "Dir Type: 'dir_entry'\n");
                    fprintf(analyzer_tester_output, "Label name: '%s'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.label_name);
                } 
                
                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_extern)
                {
                    fprintf(analyzer_tester_output, "Dir Type: 'dir_extern'\n");
                    fprintf(analyzer_tester_output, "Label name: '%s'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.label_name);
                } 
                
                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_string)
                {
                    fprintf(analyzer_tester_output, "Dir Type: 'dir_string'\n");
                    fprintf(analyzer_tester_output, "String: '%s'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.string);
                } 

                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_data)
                {
                    fprintf(analyzer_tester_output, "Dir Type: 'dir_data'\n");
                    for(j = 0; j < analyzed_line_result.dir_or_inst.directive.dir_operand.data.data_count; j++)
                        fprintf(analyzer_tester_output, "'%d'\t", analyzed_line_result.dir_or_inst.directive.dir_operand.data.data[j]);
                    fprintf(analyzer_tester_output, "\nData Count: '%d'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.data.data_count);
                } 

                fprintf(analyzer_tester_output, "\n");
            }

            /* Print inst */
            else if (analyzed_line_result.analyzed_line_opt == instruction) 
            {
                fprintf(analyzer_tester_output, "Line Type: 'instruction'\n");
                fprintf(analyzer_tester_output, "Instruction Enum Code: '%d'\n",analyzed_line_result.dir_or_inst.instruction.inst_opt);
                
                
                for (j = 0; j < 2; j++)
                {                    
                    if (analyzed_line_result.dir_or_inst.instruction.inst_operand_options[j] == operand_const_number)
                    {
                        fprintf(analyzer_tester_output, "Addresing type for operand number '%d': 'const_number'\n", j);
                        fprintf(analyzer_tester_output, "Operand number '%d' const number: '%d'\n", j, analyzed_line_result.dir_or_inst.instruction.inst_operands[j].const_number);
                    }

                    else if (analyzed_line_result.dir_or_inst.instruction.inst_operand_options[j] == operand_register)
                    {
                        fprintf(analyzer_tester_output, "Addresing type for operand number '%d': 'register'\n", j);
                        fprintf(analyzer_tester_output, "Operand number '%d' reg number: '%d'\n", j, analyzed_line_result.dir_or_inst.instruction.inst_operands[j].register_number);
                    }

                    else if (analyzed_line_result.dir_or_inst.instruction.inst_operand_options[j] == operand_label) 
                    {
                        fprintf(analyzer_tester_output, "Addresing type for operand number '%d': 'label'\n", j);
                        fprintf(analyzer_tester_output, "Operand number '%d' Label: '%s'\n", j, analyzed_line_result.dir_or_inst.instruction.inst_operands[j].label);
                    }
                }
                
                fprintf(analyzer_tester_output, "\n");
            }

            /* Invalid lines */
            else 
            {
                fprintf(analyzer_tester_output, "Line Type: 'BUG'\n\n");
            }
        }
    }

    fclose(am_file);
    fclose(analyzer_tester_output);
    return 0;
}
