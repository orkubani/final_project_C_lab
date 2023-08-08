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
 * @brief Split two instruction's operands
 *
 * @param inst_content Two operands with a comma that splits them.
 * @param first_operand Pointer to save to the first_operand
 * @param second_operand Pointer to save to the second_operand
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