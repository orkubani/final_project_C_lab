#include "macro_table.h"
#include "../helpers/utils.h"
#include <stdio.h>
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

/**
 * Different types of lines in the as file.
 */
enum line_type
{
    blank,          /**< Blank line. */
    comment,        /**< Comment line. */
    macro_def,      /**< Macro definition line. E.G "macro m1". */
    macro_end,      /**< End of a macro definition. "endmcro". */
    macro_call,     /**< Line containing a macro call. E.G m1. */
    any_other_line  /**< Any other type of line. */  
};

/**
 * @brief Checks if the given line is a macro definition.
 *
 * @param line The input line to check.
 * @return 1 if the line is a macro definition (starts with "mcro "), 0 otherwise.
 */
int is_macro_def(char *line);

/**
 * @brief Checks if the given line is a macro call.
 *
 * @param macro The macro table to search for the macro call.
 * @param line The input line to check.
 * @return 1 if the line is a macro call, 0 otherwise.
 */
int is_macro_call(Macro * macro, char *line);

/**
 * @brief Deploys a macro by writing its lines to the am file.
 *
 * @param output_file The output file, ".am", where the macro lines will be written.
 * @param macro The macro table to search for the macro to deploy.
 * @param line The input line containing the macro call.
 */
void deploy_macro(FILE * output_file, Macro * macro, char * line);

/**
 * @brief Checks the type of the input line.
 *
 * @param macro The macro table used for checking macro calls.
 * @param line The input line to analyze.
 * @return The type of the line as per the enum `line_type`.
 */
enum line_type get_line_type(Macro * macro, char *line);


/**
 * @brief Gets the macro name from a macro def line.
 *
 * @param line The input line containing the macro def.
 * @return The macro name.
 * @note The function uses the remove_white_spaces() from utils, and assums the macro name is started in index 4 (after the "mcro" string)
 */
char * get_macro_name_from_line(char * line);

/**
 * @brief Processes the input file ".as" with the specified filename and creates an ".am" output file.
 * The output file will contain the expanded macros and other lines as they appear in the input file.
 *
 * @param filename The name of the input file (without the .as extension).
 * @return The name of the output file with ".am" extension or NULL on error.
 * @note The function dynamically allocates memory for the output filename, which must be freed by the caller.
 */
char * process_as_file(char * filename);

#endif /* PREPROCESSOR_H */
