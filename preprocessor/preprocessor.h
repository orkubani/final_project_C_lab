#include "macro_table.h"
#include "../helpers/utils.h"
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

enum line_type
{
    blank,
    comment,
    macro_def,
    macro_end,
    macro_call,
    any_other_line
};

int is_macro_def(char *line);

int is_macro_call(Macro_Table *table, char *line);

enum line_type get_line_type(Macro_Table *table, char *line);

#endif /* PREPROCESSOR_H */
