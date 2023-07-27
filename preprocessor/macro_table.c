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
    macro.lines = NULL;
    macro.num_of_lines = 0;
    return macro;
}
