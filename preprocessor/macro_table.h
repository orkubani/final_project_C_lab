#include "../helpers/utils.h"
#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

typedef struct macro
{
    char name[MAX_LINE_LENGTH];
    char **lines;
    int num_of_lines;
    struct macro *next_macro;
} Macro;


Macro * create_macro(char macro_name[MAX_LINE_LENGTH]);
Macro * insert_macro_to_table(Macro *macro, char * name);
Macro * get_macro(Macro * macro, const char * macro_name);
void insert_macro_line(Macro *macro, const char *line);
void free_macro(Macro *macro);

#endif /* MACRO_TABLE_H */
