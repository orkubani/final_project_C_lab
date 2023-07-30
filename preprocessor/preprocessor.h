#include "macro_table.h"
#include "../helpers/utils.h"
#include <stdio.h>
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

int is_macro_call(Macro * macro, char *line);

void deploy_macro(FILE * output_file, Macro * macro, char * line);

enum line_type get_line_type(Macro * macro, char *line);

char * process_as_file(char * filename);

#endif /* PREPROCESSOR_H */
