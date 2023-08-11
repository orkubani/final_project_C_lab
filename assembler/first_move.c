#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>

/* First move on the am_file. */
int first_move(FILE * am_file/*, Object_File * object_file*/, const char * am_filename)
{
    char line[MAX_LINE_LENGTH] = {0}; /* Initilize line */
    Analyzed_line analyzed_line;
    Compiled_Line * data_section;
    Compiled_Line * code_section;
    int line_index = 1;
    unsigned int word = 0;

    while (fgets(line, sizeof(line), am_file)) 
    {
        analyzed_line = get_analyzed_line(line);

        if (is_valid_analyzed_line(&analyzed_line) == FALSE)
        {
            printf("Error in line '%d'! %s\n", line_index, analyzed_line.syntax_error);
            line_index++;
            continue;
        }

        /* Handle Main Label Here */

        if (analyzed_line.analyzed_line_opt == directive)
        {
            /* Implement Here */
            return TRUE;
        }

        else if (analyzed_line.analyzed_line_opt == instruction) 
        {
            /* Implement Here */
            return TRUE;
        }
    } 

    /* First Move failed */
    return FALSE;
}