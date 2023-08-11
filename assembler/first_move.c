#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>


/* Create "compiled instruction" / "compile directive" Node */
Compiled_Line * create_compiled_line()
{
    Compiled_Line * compiled_inst = NULL;
    compiled_inst = (Compiled_Line *)calloc(1, sizeof(Compiled_Line));
    if (compiled_inst == NULL)
    {
        printf("%s\n", "Allocation failed for a new compiled_inst");
        exit(0);
    }

    compiled_inst->dir_words = NULL;
    compiled_inst->num_of_words = 0;
    compiled_inst->next_compiled_line = NULL;

    return compiled_inst;
}

