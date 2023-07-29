#include <stdio.h>
#include <string.h>
#include "preprocessor.h"

enum line_type get_line_type(char *line)
{
    if (*line == COMMENT_PREFIX)
    {
        return comment;
    }

    return any_other_line;
}


int main()
{
    char blank_test[81];
    char comment_test[81];
    char macro_def_test_before_clean[81] = "        mcro m1";
    char macro_def_test[81];
    char macro_end_test[81];
    char macro_call_test[81];
    char any_other_line_test[81];

    remove_white_spaces("                       ", blank_test); 
    printf("Blank Test: %d\n", get_line_type(blank_test));

    remove_white_spaces("; Cristiano Ronaldo", comment_test);
    printf("Comment Test: %d\n", get_line_type(comment_test));

    remove_white_spaces(macro_def_test_before_clean, macro_def_test);
    printf("macro def test: %d\n", get_line_type(macro_def_test));

    remove_white_spaces("        endmcro", macro_end_test); 
    printf("macro end test: %d\n", get_line_type(macro_end_test));

    remove_white_spaces("        m1", macro_call_test);
    printf("macro call test: %d\n", get_line_type(macro_call_test));

    remove_white_spaces("L1:     inc K", any_other_line_test);
    printf("any other line test: %d\n", get_line_type(any_other_line_test));

    return 0;
}