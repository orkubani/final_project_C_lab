#include "preprocessor/preprocessor.h"
#include "analyzer/analyzer.h"
#include <stdio.h>


int main(int argc, char **argv)
{
    int i;
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

            
            if (analyzed_line_result.analyzed_line_opt == 0)
            {
            printf("Line: %s", line);
            printf("Line Type: %d\n", analyzed_line_result.analyzed_line_opt);
            printf("Dir type: %d\n",analyzed_line_result.dir_or_inst.directive.dir_opt);
            
            if (analyzed_line_result.dir_or_inst.directive.dir_opt == 0 || analyzed_line_result.dir_or_inst.directive.dir_opt == 1) 
            {
                printf("Label name: %s\n",analyzed_line_result.dir_or_inst.directive.dir_operand.label_name);
            }

            if (analyzed_line_result.dir_or_inst.directive.dir_opt == 2) 
            {
                printf("String content: %s\n",analyzed_line_result.dir_or_inst.directive.dir_operand.string);
            }

            printf("\n");
            } 
            
        }
    }

    return 0;
}
