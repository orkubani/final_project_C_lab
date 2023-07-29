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

char * get_macro_name_from_line(char * line)
{
    int i;
    char* clean_line = (char*)calloc(MAX_FILE_NAME_LENGTH, sizeof(char));
    char* macro_name = (char*)calloc(MAX_FILE_NAME_LENGTH, sizeof(char));

    if (clean_line == NULL) 
    {
        printf("Error allocating memory for the clean_line in get_macro_name_from_line.\n");
        return NULL;
    }

    if (macro_name == NULL) 
    {
        printf("Error allocating memory for the macro_name in get_macro_name_from_line.\n");
        return NULL;
    }
    
    remove_white_spaces(line, clean_line);
    strncpy(macro_name, clean_line + 4, MAX_LINE_LENGTH - 4);
    return macro_name;
}

char * process_as_file(char * filename)
{
    FILE *input_file;
    FILE *output_file;
    Macro_Table macro_table;
    char * line = (char*)calloc(MAX_LINE_LENGTH, sizeof(char)); 

    char* input_filename = (char*)calloc(MAX_FILE_NAME_LENGTH, sizeof(char));
    char* output_filename = (char*)calloc(MAX_FILE_NAME_LENGTH, sizeof(char));

    if (input_filename == NULL) 
    {
        printf("Error allocating memory for the input filename.\n");
        return NULL;
    }

    if (output_filename == NULL) 
    {
        printf("Error allocating memory for the output filename.\n");
        return NULL;
    }

    macro_table = create_macro_table();

    strcpy(input_filename, filename);
    strcat(input_filename, ".as");

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) 
    {
        printf("Error opening the input file.\n");
        return NULL;
    }

    strcpy(output_filename, filename);
    strcat(output_filename, ".am");

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) 
    {
        printf("Error opening the output file.\n");
        return NULL;
    }

    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) 
    {
        enum line_type current_line_type;
        current_line_type = get_line_type(&macro_table, line);

        if (current_line_type == macro_def)
        {
            char * macro_name;
            printf("%s\n", line);
            macro_name = get_macro_name_from_line(line);
            printf("%s\n", macro_name);
            free(macro_name);
        } 

        if (current_line_type == any_other_line)
        {
            fputs(line, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);
    free(input_filename);
    free(line);
    /* Free Macros Here */
    free_macro_table(&macro_table);
    return output_filename;
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

    /*char line[MAX_LINE_LENGTH];*/
    char * result = process_as_file("input_test_file");
    /*FILE * result_check = fopen(result, "r");
    while (fgets(line, sizeof(line), result_check) != NULL) 
    {
        printf("%s\n", line);
    }*/

    free(result);
    return 0;
}