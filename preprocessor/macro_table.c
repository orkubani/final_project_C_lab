#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 81


typedef struct macro
{
    char name[MAX_LINE_LENGTH];
    char **lines;
    int num_of_lines;
}Macro;


typedef struct macro_table
{
    Macro **macros;
    int num_of_macros;
}Macro_Table;


Macro_Table create_macro_table()
{
    Macro_Table macro_table;
    macro_table.macros = calloc(1, sizeof(char**));;
    macro_table.num_of_macros = 0;
    return macro_table;
}


Macro create_macro(char macro_name[MAX_LINE_LENGTH])
{
    Macro macro;
    strcpy(macro.name, macro_name);
    macro.lines = calloc(1, sizeof(char**));
    macro.num_of_lines = 0;
    return macro;
}


void insert_macro_line(Macro *macro, const char *line)
{
    macro->lines[macro->num_of_lines] = calloc(MAX_LINE_LENGTH, sizeof(char));
    if (macro->lines[macro->num_of_lines] == NULL)
    {
        printf("Memory allocation failed.\n");
        /*TODO Check if needed to return NULL*/
        exit(0);
    }
    strcpy(macro->lines[macro->num_of_lines], line);
    macro->num_of_lines += 1;
}


void insert_macro_to_table(Macro_Table *table, Macro *macro)
{
    table->macros[table->num_of_macros] = calloc(1, sizeof(*macro));
    if (table->macros[table->num_of_macros] == NULL)
    {
        printf("Memory allocation failed.\n");
        /*TODO Check if needed to return NULL*/
        exit(0);
    }
    table->macros[table->num_of_macros] = macro;
    table->num_of_macros += 1;
}


Macro * get_macro(Macro_Table *table, const char * macro_name)
{
    int i;
    for (i = 0; i < table->num_of_macros; i++)
    {
        if (strcmp(table->macros[i]->name, macro_name) == 0)
            return table->macros[i];
    }

    return NULL;
}


void free_macro(Macro *macro) 
{
    int i;
    
    if (macro == NULL)
        return;

    for (i = 0; i < macro->num_of_lines; i++) 
    {
        free(macro->lines[i]);
    }

    free(macro->lines);
}


void free_macro_table(Macro_Table *table) 
{
    if (table == NULL)
        return;

    free(table->macros);
}
