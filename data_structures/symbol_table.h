#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../helpers/utils.h"

#define ARE_INDENTATION 2
#define ARE_EXTERN 1 /* 0B01*/
#define ARE_NEW 2 /* 0B10 */

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
 * @param address The address of the label.
 * @return Pointer to the Symbol Node. 
 */
Symbol * create_symbol(char * symbol_name, unsigned int def_line, int symbol_opt, unsigned int * address);

/**
 * @brief Inserts a new symbol into the symbol table table.
 * 
 * @param symbol The symbol table.
 * @param symbol_name The name of the Symbol.
 * @param def_line The defenition line of the Symbol.
 * @param symbol_opt The type of the symbol.
 * @param address The address of the label.
 * @return Pointer to the Symbol Table.
 */
Symbol * insert_symbol_to_table(Symbol *symbol, char * symbol_name, unsigned int def_line, int symbol_opt, unsigned int * address);

/**
 * @brief Searches for a symbol with the symbol_name into the symbol table.
 * 
 * @param symbol The symbol table.
 * @param symbol_name The name of the Symbol.
 * @return Pointer to the required Symbol or NULL if isn't exist.
 */
Symbol * get_symbol(Symbol *symbol, char * symbol_name);

/**
 * @brief Searches for a symbol in the symbol table and returns the symbol's address if the symbol was declared.
 * 
 * @param symbol The symbol table.
 * @param symbol_name The name of the Symbol.
 * @return Address for the symbol if declared. Otherwisw returns 0.
 */
unsigned int get_symbol_def_address(Symbol *symbol, char * symbol_name);

/**
 * @brief Get "entry" symbols that are using as a start point.
 * 
 * @param symbol_table The symbol table.
 * @param entry_calls The entry calls table.
 * @return Pointer to the entry calls table.
 */
Symbol * get_entry_calls(Symbol * symbol_table, Symbol * entry_calls);

/**
 * @brief Frees the memory allocated for a given symbol.
 * 
 * @param symbol A symbol Node.
 */
void free_symbol(Symbol *symbol); 


/**
 * @brief Frees the entire symbol table and all the symbols it contains.
 * 
 * @param symbol The symbol table.
 */
void free_symbol_table(Symbol *symbol); 

#endif /* SYMBOL_TABLE_H */