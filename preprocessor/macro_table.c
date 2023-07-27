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
    macro_table.macros = NULL;
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
    macro->lines[macro->num_of_lines] = calloc(1, sizeof(char *));
    if (macro->lines[macro->num_of_lines] == NULL)
    {
        printf("Memory allocation failed.\n");
        /*TODO Check if needed to return NULL*/
        exit(0);
    }
    strcpy(macro->lines[macro->num_of_lines], line);
    macro->num_of_lines += 1;
}


/* Tester 
int main()
{    
    int i;
    Macro first_macro;
    first_macro = create_macro("First Macro");
    insert_macro_line(&first_macro, "Test1");
    insert_macro_line(&first_macro, "Test2");
    for (i=0;i<first_macro.num_of_lines;i++)
    {
        printf("%s\n",first_macro.lines[i]);
    }
    
    return 0; 
} */