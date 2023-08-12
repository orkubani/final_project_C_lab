#include "compiled_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Create "compiled instruction" / "compile directive" Node */
Compiled_Line * create_compiled_line(int line_index, int * begin_address)
{
    Compiled_Line * compiled_inst = NULL;
    compiled_inst = (Compiled_Line *)calloc(1, sizeof(Compiled_Line));
    if (compiled_inst == NULL)
    {
        printf("%s\n", "Allocation failed for a new compiled_inst");
        exit(0);
    }

    compiled_inst->line_index = line_index;
    compiled_inst->words = NULL;
    compiled_inst->num_of_words = 0;
    compiled_inst->begin_address = *begin_address;
    compiled_inst->end_address = compiled_inst->begin_address;
    strcpy(compiled_inst->missing_label[0], "\0");
    strcpy(compiled_inst->missing_label[1], "\0");
    compiled_inst->next_compiled_line = NULL;

    return compiled_inst;
}

/* Inserts a new compiled_line with the given line_index into the compiled_line table. */
Compiled_Line * insert_compiled_line_to_table(Compiled_Line *compiled_line, int line_index, int * begin_address)
{
   if (compiled_line == NULL) 
   {
        compiled_line = create_compiled_line(line_index, begin_address);
        return compiled_line;
   }

   else if (compiled_line->next_compiled_line == NULL) 
   {
        compiled_line->next_compiled_line = create_compiled_line(line_index, begin_address);
        compiled_line->next_compiled_line->next_compiled_line = NULL;
        return compiled_line;
   } 
   
   insert_compiled_line_to_table(compiled_line->next_compiled_line, line_index, begin_address);
   return compiled_line;
}

/* Searches for a Compiled_Line with the line_index into the compiled_line table. */
Compiled_Line * get_compiled_line(Compiled_Line *compiled_line, int line_index)
{
    while (compiled_line != NULL)
    {
        if (compiled_line->line_index == line_index) 
            return compiled_line;
        
        compiled_line = compiled_line->next_compiled_line;
    }

    return NULL;
}

/* Inserts a new word into the words array of the given Compiled_Line. */
void insert_word(Compiled_Line *compiled_line, unsigned int word, int * address)
{
    compiled_line->num_of_words += 1;
    compiled_line->words = (unsigned int *)realloc(compiled_line->words, compiled_line->num_of_words * sizeof(unsigned int));
    if (compiled_line->words == NULL)
    {
        printf("Memory allocation failed for a new word.\n");
        exit(0);
    }
    compiled_line->words[compiled_line->num_of_words - 1] = word;
    compiled_line->end_address = *address;
    *address += 1;
}

/* Frees the memory allocated for the given Compiled_Line and its associated Words. */
void free_compiled_line(Compiled_Line *compiled_line) 
{
    free(compiled_line->words);
    free(compiled_line);
}

/* Frees the entire compiled_line table and all the compiled_line it contains. */
void free_compiled_line_table(Compiled_Line *compiled_line) 
{
    while (compiled_line != NULL) 
    {
        Compiled_Line *temp = compiled_line;
        compiled_line = compiled_line->next_compiled_line;
        free_compiled_line(temp);
    }
}