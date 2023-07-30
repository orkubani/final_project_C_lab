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
    remove_white_spaces(line, clean_line);


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

void deploy_macro(FILE * output_file, Macro * macro, char * line)
{
    int i;
    Macro * macro_to_deploy = NULL;
    char * macro_name = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
    char * clean_macro_line = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
    remove_white_spaces(line, macro_name);
    macro_to_deploy = get_macro(macro, macro_name);
    for (i = 0; i < macro_to_deploy->num_of_lines; i++)
    {
        remove_macro_indentation(macro_to_deploy->lines[i], clean_macro_line);
        fputs(clean_macro_line, output_file);
    }

    free(clean_macro_line);
    free(macro_name);
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
    
    remove_white_spaces(line, clean_line);
    strncpy(macro_name, clean_line + 4, MAX_LINE_LENGTH - 4);
    free(clean_line);
    return macro_name;
}

char * process_as_file(char * filename)
{
    FILE *input_file;
    FILE *output_file;
    int is_macro_on = 0;
    Macro *macro_table = NULL;
    Macro *macro_on = NULL;
    
    
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

    /* Handle input file*/
    strcpy(input_filename, filename);
    strcat(input_filename, ".as");
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) 
    {
        printf("Error opening the input file.\n");
        return NULL;
    }

    /* Handle output file */
    strcpy(output_filename, filename);
    strcat(output_filename, ".am");
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) 
    {
        printf("Error opening the output file.\n");
        return NULL;
    }


    /* Analyze each line and perform the relevant action */
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) 
    {
        enum line_type current_line_type;
        current_line_type = get_line_type(macro_table, line);
        
        if (current_line_type == blank)
        {
            continue;
        }

        else if (current_line_type == comment)
        {
            continue;
        }

        else if (current_line_type == macro_end)
        {
            is_macro_on = 0;
        }

        else if(is_macro_on)
        {
            insert_macro_line(macro_on, line);
            continue;
        }

        else if (current_line_type == macro_def)
        {
            char * macro_name;
            is_macro_on = 1;
            macro_name = get_macro_name_from_line(line);
            macro_table = insert_macro_to_table(macro_table, macro_name);
            macro_on = get_macro(macro_table, macro_name);
            free(macro_name);
        }

        else if (current_line_type == macro_call)
        {
            deploy_macro(output_file, macro_table, line);
            continue;
        }

        else /* any_other_line */
            fputs(line, output_file);

    }

    fclose(input_file);
    fclose(output_file);
    free(input_filename);
    free(line);
    free_macro_table(macro_table);
    return output_filename;
}
