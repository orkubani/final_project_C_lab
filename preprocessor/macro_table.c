#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_table.h"


/* Creates a new Macro struct and initializes it with the macro_name. */
Macro * create_macro(char macro_name[MAX_LINE_LENGTH])
{
    Macro *macro = NULL;
    macro = (Macro *)calloc(1, sizeof(Macro));
    if (macro == NULL)
    {
        printf("%s\n", "Allocation failed for a new macro");
        exit(0);
    }

    strcpy(macro->name, macro_name);
    macro->lines = calloc(1, sizeof(char**));
    macro->num_of_lines = 0;
    macro->next_macro = NULL;
    return macro;
}

/* Inserts a new macro with the given macro name into the macro table. */
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

/* Searches for a macro with the given name in the macro table. */
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

/* Inserts a new line into the lines array of the given macro. */
void insert_macro_line(Macro * macro, const char *line)
{
    macro->lines[macro->num_of_lines] = calloc(MAX_LINE_LENGTH, sizeof(char));
    if (macro->lines[macro->num_of_lines] == NULL)
    {
        printf("Memory allocation failed for a new macro's line.\n");
        exit(0);
    }
    strcpy(macro->lines[macro->num_of_lines], line);
    macro->num_of_lines += 1;
}

/* Frees the memory allocated for the lines array of a given macro. */
void free_macro_lines(Macro *macro) 
{
    int i = 0;

    for (i = 0; i < macro->num_of_lines; i++) 
    {
        free(macro->lines[i]);
    }
    free(macro->lines);
}

/* Frees the memory allocated for the given macro and its associated lines. */
void free_macro(Macro *macro) 
{
    free_macro_lines(macro);
    free(macro);
}

/* Frees the entire macro table and all the macros it contains. */
void free_macro_table(Macro *macro) 
{
    while (macro != NULL) 
    {
        Macro *temp = macro;
        macro = macro->next_macro;
        free_macro(temp);
    }
}
