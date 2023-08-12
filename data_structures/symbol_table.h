#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../helpers/utils.h"

typedef struct Symbol
{
	char symbol_name[MAX_LABEL_LENGTH];
	unsigned int def_line;
    unsigned int address;
    enum
    {
        symbol_local_code,
        symbol_local_data,

        symbol_extern_def,
        symbol_extern_code,
        symbol_extern_data,

        symbol_entry_def,
        symbol_entry_code,
        symbol_entry_data
    }symbol_opt;
	struct Symbol *next_symbol;

} Symbol;

/**
 * @brief Create symbol Node
 * 
 * @param symbol_name The name of the Symbol.
 * @param def_line The defenition line of the Symbol.
 * @param symbol_opt The type of the symbol.
 */
Symbol * create_symbol(char * symbol_name, unsigned int def_line, int symbol_opt);

/**
 * @brief Inserts a new symbol into the symbol table table.
 * 
 * @param symbol The symbol table.
 * @param symbol_name The name of the Symbol.
 * @param def_line The defenition line of the Symbol.
 * @param symbol_opt The type of the symbol.
 */
Symbol * insert_symbol_to_table(Symbol *symbol, char * symbol_name, unsigned int def_line, int symbol_opt);

/**
 * @brief Searches for a symbol with the symbol_name into the symbol table.
 * 
 * @param symbol The symbol table.
 * @param symbol_name The name of the Symbol.
 */
Symbol * get_symbol(Symbol *symbol, char * symbol_name);

#endif /* SYMBOL_TABLE_H */