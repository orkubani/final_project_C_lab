#ifndef COMPILED_LINE_H
#define COMPILED_LINE_H

#include "../helpers/utils.h"
/* "Instruction" / "Directive" Compiled Line */
typedef struct Compiled_Line /* Code section */
{
    int line_index;
    unsigned int * words;
    int num_of_words;
    unsigned int begin_address;
    unsigned int end_address;
    enum
    {
        src_label,
        dest_label
    }missing_label_op_type[2];
    char missing_label[2][MAX_LABEL_LENGTH]; /* Will be found in the second_move */
    struct Compiled_Line *next_compiled_line;

}Compiled_Line;


/**
 * @brief Create "compiled instruction" / "compile directive" Node.
 * 
 * @param line_index The line index from the am_file.
 * @param begin_address for the new compiled_line
 * @return Pointer to the compiled_line Node.
 */
Compiled_Line * create_compiled_line(int line_index, unsigned int * begin_address);

/**
 * @brief Inserts a new compiled_line with the given line_index into the compiled_line.
 * 
 * @param line_index The line index from the am_file.
 * @param compiled_line Pointer to the compiled_line table
 * @param begin_address for the new compiled_line
 * @return Pointer to the compiled_line Node.
 */
Compiled_Line * insert_compiled_line_to_table(Compiled_Line *compiled_line, int line_index, unsigned int *begin_address);

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
 * @param address for the new word.
 */
void insert_word(Compiled_Line *compiled_line, unsigned int word, unsigned int * address);

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

#endif /* COMPILED_LINE_H */