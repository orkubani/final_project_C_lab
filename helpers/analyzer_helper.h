#ifndef ANALYZER_HELPER_H
#define ANALYZER_HELPER_H

#include "utils.h"
#include "../analyzer/analyzer.h"

/**
 * @brief Remove the str quotations to save it as is.
 *
 * @param str_content The string content with quotations.
 */
char * remove_str_quotations(char * str_content);

/**
 * @brief 
 *
 * @param 
 * @param 
 */
void split_operands(const char *inst_content, char *first_operand, char *second_operand);

/**
 * @brief 
 *
 * @param 
 * @param 
 */
int get_reg_num(char * reg);

#endif /* ANALYZER_HELPER_H */