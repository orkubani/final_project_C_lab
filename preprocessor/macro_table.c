#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_table.h"


Macro_Table create_macro_table()
{
    Macro_Table macro_table;
    macro_table.macros = calloc(1, sizeof(char**));;
    macro_table.num_of_macros = 0;
    return macro_table;
}


Macro * create_macro(char macro_name[MAX_LINE_LENGTH])
{
    Macro *macro = NULL;
    macro = (Macro *)calloc(1, sizeof(Macro));
    if (macro == NULL)
    {
        printf("%s\n", "Allocation failed for create_macro");
        exit(0);
    }

    strcpy(macro->name, macro_name);
    macro->lines = calloc(1, sizeof(char**));
    macro->num_of_lines = 0;
    macro->next_macro = NULL;
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


Macro * insert_macro_to_table(Macro *macro, char * name)
{
   if (macro->next_macro == NULL) 
   {
        macro->next_macro = create_macro(name);
        macro->next_macro->next_macro = NULL;
        return macro->next_macro;
   } 
   
   insert_macro_to_table(macro->next_macro, name);
   return macro->next_macro;
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
