#ifndef ANALYZER_HELPER_H
#define ANALYZER_HELPER_H

char * remove_str_quotations(char * str_content);
void split_operands(const char *inst_content, char *first_operand, char *second_operand);

#endif /* ANALYZER_HELPER_H */