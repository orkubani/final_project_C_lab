#include "preprocessor/preprocessor.h"
#include "analyzer/analyzer.h"
#include <stdio.h>


int main(int argc, char **argv)
{
    int i;
    int j;
    char * am_filename;
    FILE * am_file;
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

        /* Analyze each line and perform the relevant action */
        while (fgets(line, MAX_LINE_LENGTH, am_file) != NULL) 
        {
            analyzed_line_result = get_analyzed_line(line);
            printf("Line: %s", line);
            printf("Main Label: '%s'\n", analyzed_line_result.label_name);

            /* Print dir */
            if (analyzed_line_result.analyzed_line_opt == directive)
            {
                printf("Line Type: 'directive'\n");

                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_entry)
                {
                    printf("Dir Type: 'dir_entry'\n");
                    printf("Label name: '%s'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.label_name);
                } 
                
                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_extern)
                {
                    printf("Dir Type: 'dir_extern'\n");
                    printf("Label name: '%s'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.label_name);
                } 
                
                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_string)
                {
                    printf("Dir Type: 'dir_string'\n");
                    printf("String: '%s'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.string);
                } 

                if (analyzed_line_result.dir_or_inst.directive.dir_opt == dir_data)
                {
                    printf("Dir Type: 'dir_data'\n");
                    for(j = 0; j < analyzed_line_result.dir_or_inst.directive.dir_operand.data.data_count; j++)
                        printf("'%d'\t", analyzed_line_result.dir_or_inst.directive.dir_operand.data.data[j]);
                    printf("\nData Count: '%d'\n", analyzed_line_result.dir_or_inst.directive.dir_operand.data.data_count);
                } 

                printf("\n");
            }

            /* Print inst */
            else if (analyzed_line_result.analyzed_line_opt == instruction) 
            {
                printf("Line Type: 'instruction'\n");
                printf("Inst opt: '%d'\n\n",analyzed_line_result.dir_or_inst.instruction.inst_opt);
            }

            /* Invalid lines */
            else 
            {
                printf("Line Type: 'BUG'\n\n");
            }
        }
    }

    return 0;
}
