#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

#define MAX_LINE_LENGTH 81

typedef struct macro
{
    char name[MAX_LINE_LENGTH];
    char **lines;
    int num_of_lines;
} Macro;

typedef struct macro_table
{
    Macro **macros;
    int num_of_macros;
} Macro_Table;

Macro_Table create_macro_table();
Macro create_macro(char macro_name[MAX_LINE_LENGTH]);
void insert_macro_line(Macro *macro, const char *line);
void insert_macro_to_table(Macro_Table *table, Macro *macro);
Macro *get_macro(Macro_Table *table, const char *macro_name);
void free_macro(Macro *macro);
void free_macro_table(Macro_Table *table);

#endif /* MACRO_TABLE_H */
