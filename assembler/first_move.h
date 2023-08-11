#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H

#define BASE_ADDRESS 100

/* "Instruction" / "Directive" Compiled Line */
typedef struct Compiled_Line /* Code section */
{
    int line_index;
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
 * @param line_index The line index from the am_file.
 * @return Pointer to the compiled_line Node.
 */
Compiled_Line * create_compiled_line(int line_index);

/**
 * @brief Inserts a new compiled_line with the given line_index into the compiled_line.
 * 
 * @param line_index The line index from the am_file.
 * @param compiled_line Pointer to the compiled_line table
 * @return Pointer to the compiled_line Node.
 */
Compiled_Line * insert_compiled_line_to_table(Compiled_Line *compiled_line, int line_index);

#endif /* FIRST_MOVE_H */