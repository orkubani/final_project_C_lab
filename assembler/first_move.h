#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H

#include "../helpers/utils.h"
#include "../analyzer/analyzer.h"
#include "../helpers/analyzer_helper.h"
#include "../data_structures/compiled_line.h"
#include <stdio.h>

#define BASE_ADDRESS 100

typedef struct Object_File 
{

}Object_File;

/**
 * @brief First move on the am_file.
 * 
 * @param am_file Pointer to the am_file.
 * @param object_file Pointer to a struct thats hold the relevant data for the object file.
 * @param am_filename The am filename.
 *
 * @return TRUE (1) if there are no errors, FALSE (0) if there are errors and the process failed
 */
int first_move(FILE * am_file, Object_File * object_file, const char * am_filename);
#endif /* FIRST_MOVE_H */