#ifndef ANALYZER_HELPER_H
#define ANALYZER_HELPER_H

#include "utils.h"
#include "../analyzer/analyzer.h"

char * remove_str_quotations(char * str_content);
void split_operands(const char *inst_content, char *first_operand, char *second_operand);
int get_reg_num(char * reg);

#endif /* ANALYZER_HELPER_H */