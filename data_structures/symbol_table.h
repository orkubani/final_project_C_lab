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
    };
	struct Symbol *next_symbol;

} Symbol;

#endif /* SYMBOL_TABLE_H */