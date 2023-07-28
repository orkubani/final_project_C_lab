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

/* Tester */
int main()
{    
    int i, j;
    Macro_Table first_table;
    Macro first_macro, second_macro;

    first_macro = create_macro("First Macro");
    insert_macro_line(&first_macro, "First line of the first Macro");
    insert_macro_line(&first_macro, "Second line of the first Macro");
    insert_macro_line(&first_macro, "Third line of the first Macro");

    second_macro = create_macro("Second Macro");
    insert_macro_line(&second_macro, "First line of the second Macro");
    insert_macro_line(&second_macro, "Second line of the second Macro");
    insert_macro_line(&second_macro, "Third line of the second Macro");

    first_table = create_macro_table();
    insert_macro_to_table(&first_table, &first_macro);
    insert_macro_to_table(&first_table, &second_macro);

    for (i = 0; i < first_table.num_of_macros; i++) 
    {
        printf("Macro name: %s\n", first_table.macros[i]->name);
        printf("Macro num of lines: %d\n", first_table.macros[i]->num_of_lines);

        for(j=0; j < first_macro.num_of_lines; j++)
        {
            printf("Line number %d: %s\n", j + 1, first_table.macros[i]->lines[j]);
        }

        printf("\n");
    } 

    return 0; 
} 