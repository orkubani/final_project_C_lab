#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H

#define BASE_ADDRESS 100

/* "Instruction" / "Directive" Compiled Line */
typedef struct Compiled_Line /* Code section */
{
    int line_index;
    unsigned int ** words;
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

/**
 * @brief Searches for a Compiled_Line with the line_index into the compiled_line table.
 * 
 * @param line_index The line index from the am_file.
 * @param compiled_line Pointer to the compiled_line table
 * @return Pointer to the compiled_line Node or Null if isn't exist.
 */
Compiled_Line * get_compiled_line(Compiled_Line *compiled_line, int line_index);

/**
 * @brief Inserts a new word into the words array of the given Compiled_Line.
 * 
 * @param word to add to a given compiled_line.
 * @param compiled_line Pointer to the compiled_line to add the word to.
 */
void insert_word(Compiled_Line *compiled_line, unsigned int word);

/**
 * @brief Frees the memory allocated for the Words array of a given Compiled_Line.
 * 
 * @param compiled_line Pointer to a compiled_line Node
 */
void free_compiled_line_words(Compiled_Line *compiled_line); 

/**
 * @brief Frees the memory allocated for the given Compiled_Line and its associated Words.
 * 
 * @param compiled_line Pointer to a compiled_line Node to add the word to.
 */
void free_compiled_line(Compiled_Line *compiled_line);

/**
 * @brief Frees the entire compiled_line table and all the compiled_line it contains.
 * 
 * @param compiled_line Pointer to the compiled_line table.
 */
void free_compiled_line_table(Compiled_Line *compiled_line); 

#endif /* FIRST_MOVE_H */