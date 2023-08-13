#ifndef FILE_BUILDER_H
#define FILE_BUILDER_H

#include "../assembler/assembler.h"

#define DOT_ENT_SUFFIX ".ent"
#define DOT_EXT_SUFFIX ".ext"
#define DOT_OB_SUFFIX ".ob"


/**
 * @brief Get entry_table and build '.ent' file with all the entries defenitions' lines.
 * 
 * @param entry_table Table with all the entries defenitions' lines.
 * @param entry_filename The am_filename without the '.am' suffix.
 */
void build_entry_file(char * entry_filename, Symbol * entry_table);

/**
 * @brief Get extern_table and build '.ext' file with all the address where extern symbols are called.
 * 
 * @param extern_table Table with all the address where extern symbols are called.
 * @param extern_filename The am_filename without the '.am' suffix.
 */
void build_extern_file(char * extern_filename, Symbol * extern_table);

#endif /* FILE_BUILDER_H */