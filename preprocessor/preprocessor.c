#include <stdio.h>
#include <string.h>
#include "preprocessor.h"
# include "macro_table.h"

int is_macro_def(char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_prefix_white_spaces(line, clean_line);

    if (strncmp(clean_line, "mcro ", 5) == 0)
        return 1;
    

    return 0;
}

int is_macro_call(Macro_Table *table, char *line)
{
    char clean_line[MAX_LINE_LENGTH];
    remove_prefix_white_spaces(line, clean_line);

    if (get_macro(table, clean_line) != NULL) 
        return 1;

    return 0;
}

enum line_type get_line_type(Macro_Table *table, char *line)
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

    if (is_macro_call(table, line)) 
        return macro_call;

    return any_other_line;
}


int main()
{
    /*
    Macro_Table first_table;
    Macro first_macro;

    char blank_test_before_clean[81] = "                       ";

    char comment_test_before_clean[81] = "; Cristiano Ronaldo";
    
    char macro_def_test_before_clean[81] = "       mcro m1";
    
    char macro_end_before_clean[81] = "        endmcro";
    
    char macro_call_before_clean[81] = "        m1";
    
    char any_other_line_before_clean[81] = "L1:     inc K";

    first_macro = create_macro("m1");
    first_table = create_macro_table();

    insert_macro_line(&first_macro, "            sub @r1, @r4");
    insert_macro_line(&first_macro, "            bne END");

    insert_macro_to_table(&first_table, &first_macro);
    
    printf("Blank Test: %d\n", get_line_type(&first_table, blank_test_before_clean));

    printf("Comment Test: %d\n", get_line_type(&first_table, comment_test_before_clean));

    printf("macro def test: %d\n", get_line_type(&first_table, macro_def_test_before_clean));

    printf("macro end test: %d\n", get_line_type(&first_table, macro_end_before_clean));

    printf("macro call test: %d\n", get_line_type(&first_table, macro_call_before_clean));

    printf("any other line test: %d\n", get_line_type(&first_table, any_other_line_before_clean));

    free_macro(&first_macro);
    free_macro_table(&first_table);

    */
    return 0;
}