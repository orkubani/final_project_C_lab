#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
# include "macro_table.h"

int is_macro_def(char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_prefix_white_spaces(line, clean_line);

    if (strncmp(clean_line, "mcro ", 5) == 0)
        return 1;
    

    return 0;
}

int is_macro_call(Macro_Table *table, char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_prefix_white_spaces(line, clean_line);

    if (get_macro(table, clean_line) != NULL) 
        return 1;

    return 0;
}

enum line_type get_line_type(Macro_Table *table, char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_white_spaces(line, clean_line);

    if (*clean_line == '\0')
        return blank;
    

    if (*clean_line == COMMENT_PREFIX)
        return comment;
    

    if (strcmp(clean_line, "endmcro") == 0) 
        return macro_end;
    

    if (is_macro_def(line)) 
        return macro_def;

    if (is_macro_call(table, line)) 
        return macro_call;

    return any_other_line;
}

FILE * process_as_file(char * input_filename)
{
    FILE *input_file;
    FILE *output_file;
    Macro_Table macro_table;
    char line[MAX_LINE_LENGTH];
     /* Remeber to change*/
    char output_name[MAX_FILE_NAME_LENGTH] = "/mnt/c/Or_Kubani_Openu_CS/2023B/maabada_20476/final_project_C_lab/test_output";
    
    macro_table = create_macro_table();

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) 
    {
        printf("Error opening the input file.\n");
        return NULL;
    }

    strcat(output_name, ".am");

    output_file = fopen(output_name, "w");
    if (output_file == NULL) 
    {
        printf("Error opening the output file.\n");
        return NULL;
    }

    while (fgets(line, sizeof(line), input_file) != NULL) 
    {
        enum line_type current_line_type;
        current_line_type = get_line_type(&macro_table, line);
        if (current_line_type == any_other_line)
            fputs(line, output_file);
    }

    return output_file;
}

int main()
{
    /*

    Macro_Table first_table;
    Macro first_macro;

    first_macro = create_macro("m1");
    first_table = create_macro_table();

    insert_macro_line(&first_macro, "            sub @r1, @r4");
    insert_macro_line(&first_macro, "            bne END");

    insert_macro_to_table(&first_table, &first_macro);

    free_macro(&first_macro);
    free_macro_table(&first_table);

    */

    process_as_file("/mnt/c/Or_Kubani_Openu_CS/2023B/maabada_20476/final_project_C_lab/input_test_file.as");
    return 0;
}