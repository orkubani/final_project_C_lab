#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../helpers/utils.h"
#include "../analyzer/analyzer.h"
#include "../helpers/analyzer_helper.h"
#include "../data_structures/compiled_line.h"
#include "../data_structures/symbol_table.h"
#include <stdio.h>

#define DEST_INDENTATION 2
#define SRC_INDENTATION 9
#define OPCODE_INDENTATION 5
#define ARE_INDENTATION 2
#define DEST_REG_INDENTATION 2
#define SRC_REG_INDENTATION 7

#define BASE_ADDRESS 100

typedef struct Object_File 
{
    Compiled_Line * data_section;
    Compiled_Line * code_section;
    Symbol * symbol_table;
    Symbol * entry_calls;
    Symbol * extern_calls;
}Object_File;

/**
 * @brief First move on the am_file.
 * 
 * @param am_file Pointer to the am_file.
 * @param am_filename The am filename.
 *
 * @return Struct that contains: Symbol table, code_section, data_section, entry_table.
 */
Object_File first_move(FILE * am_file, const char * am_filename);

/**
 * @brief In this move I am going over the code section only to update the symbols' addresses 
 *
 * @param object_file Pointer to a struct with: Symbol table, code_section, data_section, entry_table.
 * @return Struct with all the required information to create the following files: '.ob' .ent' '.ext'.
 */
Object_File second_move(Object_File object_file);

/**
 * @brief Calls to the first and the second moves and calls to the releavnt methods to create the following files: '.ob' .ent' '.ext'.
 * 
 * @param am_file Pointer to the am_file.
 * @param am_filename The am filename.
 * @return True (1) pass / False (0) failed
 */
int assembler(FILE * am_file, const char * am_filename);

#endif /* ASSEMBLER_H */