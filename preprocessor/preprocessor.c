#include <string.h>
#include "preprocessor.h"
#define START_OF_COMMENT ';'

enum line_type
{
    blank,
    comment,
    macro_def,
    macro_end,
    macro_call,
    any_other_line
};

enum line_type get_line_type(char *line)
{
    remove_white_spaces(line);

    if (*line == START_OF_COMMENT)
    {
        return comment;
    }

    return any_other_line;
}