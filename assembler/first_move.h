#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H

#define BASE_ADDRESS 100

/* "Instruction" / "Directive" Compiled Line */
typedef struct Compiled_Line /* Code section */
{
    unsigned int ** dir_words;
    int num_of_words;
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
 * @return Pointer to the compiled_line Node.
 */
Compiled_Line * create_compiled_line();

#endif /* FIRST_MOVE_H */