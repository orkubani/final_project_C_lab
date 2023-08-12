#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>


/* Creates symbol Node */
Symbol * create_symbol(char * symbol_name, unsigned int def_line, int symbol_opt, int * address)
{
    Symbol * symbol = NULL;
    symbol = (Symbol *)calloc(1, sizeof(Symbol));
    if (symbol == NULL)
    {
        printf("%s\n", "Allocation failed for a new symbol");
        exit(0);
    }

    strcpy(symbol->symbol_name, symbol_name);
    symbol->def_line = def_line;
    symbol->address = *address;
    symbol->symbol_opt = symbol_opt;
    symbol->next_symbol = NULL;

    return symbol;
}

/* Inserts a new symbol into the symbol table table. */
Symbol * insert_symbol_to_table(Symbol *symbol, char * symbol_name, unsigned int def_line, int symbol_opt, int * address)
{
   if (symbol == NULL) 
   {
        symbol = create_symbol(symbol_name, def_line, symbol_opt, address);
        return symbol;
   }

   else if (symbol->next_symbol == NULL) 
   {
        symbol->next_symbol = create_symbol(symbol_name, def_line, symbol_opt, address);
        symbol->next_symbol->next_symbol = NULL;
        return symbol;
   } 
   
   insert_symbol_to_table(symbol->next_symbol, symbol_name, def_line, symbol_opt, address);
   return symbol;
}

/* Searches for a symbol with the symbol_name into the symbol table. */
Symbol * get_symbol(Symbol *symbol, char * symbol_name)
{
    while (symbol != NULL)
    {
        if (strcmp(symbol->symbol_name, symbol_name) == 0) 
            return symbol;
        
        symbol = symbol->next_symbol;
    }

    return NULL;
}