#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_table.h"

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

Macro * insert_macro_to_table(Macro *macro, char * name)
{
   if (macro == NULL) 
   {
        macro = create_macro(name);
        return macro;
   }

   else if (macro->next_macro == NULL) 
   {
        macro->next_macro = create_macro(name);
        macro->next_macro->next_macro = NULL;
        return macro;
   } 
   
   insert_macro_to_table(macro->next_macro, name);
   return macro;
}

Macro * get_macro(Macro * macro, const char * macro_name)
{
    while (macro != NULL)
    {
        if (strcmp(macro->name, macro_name) == 0) 
            return macro;
        
        macro = macro->next_macro;
    }

    return NULL;
}

void insert_macro_line(Macro * macro, const char *line)
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

void free_macro_lines(Macro *macro) 
{
    int i = 0;

    for (i = 0; i < macro->num_of_lines; i++) 
    {
        free(macro->lines[i]);
    }
    free(macro->lines);
}

void free_macro(Macro *macro) 
{
    free_macro_lines(macro);
    free(macro);
}

void free_macro_table(Macro *macro) 
{
    while (macro != NULL) 
    {
        Macro *temp = macro;
        macro = macro->next_macro;
        free_macro(temp);
    }
}
