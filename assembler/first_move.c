#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>


/* Create "compiled instruction" / "compile directive" Node */
Compiled_Line * create_compiled_line(int line_index)
{
    Compiled_Line * compiled_inst = NULL;
    compiled_inst = (Compiled_Line *)calloc(1, sizeof(Compiled_Line));
    if (compiled_inst == NULL)
    {
        printf("%s\n", "Allocation failed for a new compiled_inst");
        exit(0);
    }

    compiled_inst->line_index = line_index;
    compiled_inst->dir_words = NULL;
    compiled_inst->num_of_words = 0;
    compiled_inst->next_compiled_line = NULL;

    return compiled_inst;
}

/* Inserts a new compiled_line with the given line_index into the compiled_line. */
Compiled_Line * insert_compiled_line_to_table(Compiled_Line *compiled_line, int line_index)
{
   if (compiled_line == NULL) 
   {
        compiled_line = create_compiled_line(line_index);
        return compiled_line;
   }

   else if (compiled_line->next_compiled_line == NULL) 
   {
        compiled_line->next_compiled_line = create_compiled_line(line_index);
        compiled_line->next_compiled_line->next_compiled_line = NULL;
        return compiled_line;
   } 
   
   insert_compiled_line_to_table(compiled_line->next_compiled_line, line_index);
   return compiled_line;
}

