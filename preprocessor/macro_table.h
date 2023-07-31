#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

#include "../helpers/utils.h"

/**
 * @struct Macro
 * Represents a macro object.
 */
typedef struct macro
{
    char name[MAX_LINE_LENGTH]; /**< The name of the macro. */
    char **lines;               /**< An array of strings representing the macro's content. */
    int num_of_lines;           /**< The number of lines in the macro. */
    struct macro *next_macro;  /**< Pointer to the next macro in the macro table (linked list). */
} Macro;

/**
 * @brief Creates a new Macro struct and initializes it with the macro_name.
 *
 * @param macro_name The name of the macro to be created.
 * @return A pointer to the new created Macro.
 */
Macro * create_macro(char macro_name[MAX_LINE_LENGTH]);

/**
 * @brief Inserts a new macro with the given macro name into the macro table.
 *
 * @param macro A pointer to the head of the macro table linked list.
 * @param name The name of the macro to be inserted.
 * @return A pointer to the head of the updated macro table.
 * @note If the macro table is empty (macro is NULL), a new table is created with the given name.
 * @note If the macro table is not empty, a new macro is appended to the end of the linked list.
 */
Macro * insert_macro_to_table(Macro *macro, char * name);

/**
 * @brief Searches for a macro with the given name in the macro table.
 *
 * @param macro A pointer to the head of the macro table linked list.
 * @param macro_name The name of the macro to be searched for.
 * @return A pointer to the searched Macro if found; otherwise, returns NULL.
 */
Macro * get_macro(Macro * macro, const char * macro_name);

/**
 * @brief Inserts a new line into the lines array of the given macro.
 *
 * @param macro A pointer to the Macro struct.
 * @param line The line to be inserted into the macro.
 */
void insert_macro_line(Macro * macro, const char *line);

/**
 * @brief Frees the memory allocated for the lines array of a given macro.
 *
 * @param macro A pointer to the Macro struct.
 * @note The Macro struct itself is not freed by this function.
 */
void free_macro_lines(Macro *macro);

/**
 * @brief Frees the memory allocated for the given macro and its associated lines.
 *
 * @param macro A pointer to the Macro struct to be freed.
 * @note The function also frees the memory for the lines array in the Macro.
 */
void free_macro(Macro *macro); 

/**
 * @brief Frees the entire macro table and all the macros it contains.
 *
 * @param macro A pointer to the head of the macro table linked list.
 * @note This function should be called to free all the memory allocated for the entire macro table.
 * @note This function uses the functions free_macro and free_macro_lines.
 */
void free_macro_table(Macro *macro);  

#endif /* MACRO_TABLE_H */
