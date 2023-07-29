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

int is_macro_call(Macro *macro, char *line)
{
    Macro * tmp;
    char clean_line[MAX_LINE_LENGTH];

    tmp = macro;
    remove_prefix_white_spaces(line, clean_line);


    while (macro != NULL)
    {
        if (get_macro(macro, clean_line) != NULL) 
        {
            macro = tmp;
            return 1;
        }
        macro = macro->next_macro;
    }
    
    macro = tmp;
    return 0;
}

enum line_type get_line_type(Macro *macro, char *line)
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

    if (is_macro_call(macro, line)) 
        return macro_call;

    return any_other_line;
}

char * get_macro_name_from_line(char * line)
{
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
    
    remove_prefix_white_spaces(line, clean_line);
    strncpy(macro_name, clean_line + 5, MAX_LINE_LENGTH - 5);
    free(clean_line);
    return macro_name;
}

char * process_as_file(char * filename)
{
    FILE *input_file;
    FILE *output_file;
    Macro macro_table;
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
            macro_name = get_macro_name_from_line(line);
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
    return output_filename;
}

int main()
{
    /*Tester 
    Macro * macro_table = NULL;
    Macro *tmp = NULL;
    macro_table = insert_macro_to_table(macro_table, "first_macro");
    macro_table = insert_macro_to_table(macro_table, "second_macro");
    macro_table = insert_macro_to_table(macro_table, "third_macro");

    printf("%s\n",macro_table->name);
    printf("%s\n",(macro_table->next_macro)->name);
    printf("%s\n",(macro_table->next_macro->next_macro)->name);

    tmp = get_macro(macro_table, "second_macro");
    insert_macro_line(tmp, "first try");
    insert_macro_line(tmp, "second try");

    free_macro_table(macro_table);

    */

    char line[MAX_LINE_LENGTH];
    char * result = process_as_file("input_test_file");
    FILE * result_check = fopen(result, "r");
    while (fgets(line, sizeof(line), result_check) != NULL) 
    {
        printf("%s\n", line);
    }

    free(result);
    return 0;
}