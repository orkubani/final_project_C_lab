#include <stdio.h>
#include <string.h>
#include "preprocessor.h"

int is_macro_def(char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_prefix_white_spaces(line, clean_line);

    if (strncmp(clean_line, "mcro ", 5) == 0)
    {
        return 1;
    }

    return 0;
}

enum line_type get_line_type(char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_white_spaces(line, clean_line);

    if (*clean_line == '\0')
        return blank;
    

    if (*clean_line == COMMENT_PREFIX)
        return comment;
    

    if (strcmp(clean_line, "endmcro") == 0) 
        return macro_end;
    

    if (is_macro_def(line)) 
        return macro_def;
    
    return any_other_line;
}


int main()
{
    char blank_test_before_clean[81] = "                       ";

    char comment_test_before_clean[81] = "; Cristiano Ronaldo";
    
    char macro_def_test_before_clean[81] = "       mcro m1";
    
    char macro_end_before_clean[81] = "        endmcro";
    
    char macro_call_before_clean[81] = "        m1";
    
    char any_other_line_before_clean[81] = "L1:     inc K";
    
    printf("Blank Test: %d\n", get_line_type(blank_test_before_clean));

    printf("Comment Test: %d\n", get_line_type(comment_test_before_clean));

    printf("macro def test: %d\n", get_line_type(macro_def_test_before_clean));

    printf("macro end test: %d\n", get_line_type(macro_end_before_clean));

    printf("macro call test: %d\n", get_line_type(macro_call_before_clean));

    printf("any other line test: %d\n", get_line_type(any_other_line_before_clean));

    return 0;
}