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

        if (am_filename == NULL) 
        {
            printf("Memory allocation failed for am_filename.\n");
            exit(0);
        }

        am_filename = process_as_file(argv[i]);

        am_file = fopen(am_filename, "r"); /* Closed in the assembler() */

        if (am_file == NULL) 
        {
            printf("Failed open am_file.\n");
            exit(0);
        }

        assembler(am_file, am_filename);
        free(am_filename);
    }

    return 0;
}
