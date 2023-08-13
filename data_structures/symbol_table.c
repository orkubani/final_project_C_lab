#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>


/* Creates symbol Node */
Symbol * create_symbol(char * symbol_name, unsigned int def_line, int symbol_opt, unsigned int * address)
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
Symbol * insert_symbol_to_table(Symbol *symbol, char * symbol_name, unsigned int def_line, int symbol_opt, unsigned int * address)
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

/* Searches for a symbol in the symbol table and returns the symbol's address if the symbol was declared. */
unsigned int get_symbol_def_address(Symbol *symbol, char * symbol_name)
{
    while (symbol != NULL)
    {
        if (strcmp(symbol->symbol_name, symbol_name) == 0)
        {
            if (symbol->symbol_opt == symbol_extern_def) 
            {
                symbol->address = 0;
                symbol->address |= ARE_EXTERN;
                return symbol->address;
            }

            else if(symbol->symbol_opt != symbol_entry_def)
            {
                symbol->address = symbol->address << ARE_INDENTATION;
                symbol->address |= ARE_NEW;
                return symbol->address;
            }
        }
         
        symbol = symbol->next_symbol;
    }

    return FALSE;
}

/* Get "entry" symbols that are using as a start point. */
Symbol * get_entry_calls(Symbol * symbol_table, Symbol * entry_calls)
{
    Symbol * temp = symbol_table;

    while (temp != NULL) 
    {
        if (temp->symbol_opt == symbol_entry_code || temp->symbol_opt == symbol_entry_data) 
        {
            entry_calls = insert_symbol_to_table(entry_calls, temp->symbol_name,
             temp->def_line, temp->symbol_opt, &(temp->address));
        }

        temp = temp->next_symbol;
    }

    return entry_calls;
}


/* Frees the memory allocated for a given symbol. */
void free_symbol(Symbol *symbol) 
{
    free(symbol);
}

/* Frees the entire symbol table and all the symbols it contains. */
void free_symbol_table(Symbol *symbol) 
{
    while (symbol != NULL) 
    {
        Symbol *temp = symbol;
        symbol = symbol->next_symbol;
        free_symbol(temp);
    }
}