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
 * @brief Get the number of a given register.
 *
 * @param reg The regist in 'rX' layout.
 * @return The number of the register. 
 */
int get_reg_num(char * reg);

/**
 * @brief Checks if there is an error that raised until now regarding the current line.
 *
 * @param analyzed_line Pointer to the 'analyzed_line' obj.
 * @return TRUE (1) if Valid, otherwise returns FALSE (0). 
 */
int is_valid_analyzed_line(Analyzed_line * analyzed_line);

#endif /* ANALYZER_HELPER_H */