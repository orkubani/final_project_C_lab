#include "first_move.h"
#include <stdio.h>
#include <stdlib.h>


/* Create "compiled instruction" / "compile directive" Node */
Compiled_Line * create_compiled_line(int line_opt)
{
    Compiled_Line * compiled_inst = NULL;
    compiled_inst = (Compiled_Line *)calloc(1, sizeof(Compiled_Line));
    if (compiled_inst == NULL)
    {
        printf("%s\n", "Allocation failed for a new compiled_inst");
        exit(0);
    }

    if (line_opt == instruction)
    {
        compiled_inst->analyzed_line_opt = instruction;
        compiled_inst->Compiled_Inst.inst_word = 0;
        compiled_inst->Compiled_Inst.first_extra_word = 0;
        compiled_inst->Compiled_Inst.second_extra_word = 0;
        compiled_inst->Compiled_Inst.num_of_words = 0;
        compiled_inst->next_compiled_line = NULL;
        return compiled_inst;
    }

    else if (line_opt == directive) 
    {
        /* Implement here */
        compiled_inst->next_compiled_line = NULL;
        return compiled_inst;
    }

    return compiled_inst;
}

