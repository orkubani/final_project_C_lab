#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H

#define BASE_ADDRESS 100

/* "Instruction" / "Directive" Compiled Line */
typedef struct Compiled_Line /* Code section */
{
    enum
    {
        directive,
        instruction
    }analyzed_line_opt;
    
    struct
    {
        /* Implement Here */
    }Compiled_Dir;

    struct 
    {
        unsigned int inst_word;
        unsigned int first_extra_word;
        unsigned int second_extra_word;
        int num_of_words;
    }Compiled_Inst;

    struct Compiled_Line *next_compiled_line;

}Compiled_Line;

typedef struct Extern_Calls 
{
    /* Implement struct here */
}Extern_Calls;

typedef struct Entries_Calls 
{
    /* Implement struct here */
}Entries_Calls;

/**
 * @brief Create "compiled instruction" / "compile directive" Node.
 *
 * @param inst_opt Instruction/Directive enum code to build the right compiled line.
 * @return Pointer to the compiled_line Node
 */
Compiled_Line * create_compiled_line(int line_opt);

#endif /* FIRST_MOVE_H */