#include "assembler/assembler.h"
#include "preprocessor/preprocessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    int i;

    for (i = 1; i < argc; i++) 
    {
        FILE * am_file;
        char * am_filename = (char*)calloc(MAX_FILE_NAME_LENGTH, sizeof(char));
        if (am_filename) 
            am_filename = process_as_file(argv[i]);

        am_file = fopen(am_filename, "r");
        if (am_file) 
        {
            first_move(am_file, am_filename);
            /* Implement compilation here */
        }
    }

    return 0;
}
