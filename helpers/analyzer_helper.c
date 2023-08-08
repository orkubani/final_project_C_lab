#include "analyzer_helper.h"
#include <stdlib.h>
#include <string.h>

/* Remove the str quotations to save it as is. */
char * remove_str_quotations(char * str_content) /* Before Error System */
{
    int i;

    if (str_content == NULL)
        return NULL;

    str_content += 1;

    for(i = 0; str_content[i] != '\0'; i++)
    {
        if (str_content[i] == '\"')
        {
            str_content[i] = '\0';
        }
    }

    return str_content;
}

/* Split two instruction's operands */
void split_operands(const char *inst_content, char *first_operand, char *second_operand) /* Before Error System */
{
    int i = 0;
    int j = 0;

    while (inst_content[i] != ',' && inst_content[i] != '\0') 
    {
        first_operand[j++] = inst_content[i++];
    }
    first_operand[j] = '\0';

    i++; /* Skip the ',' */
    j = 0;

    while (inst_content[i] != '\0') 
    {
        second_operand[j++] = inst_content[i++];
    }
    
    second_operand[j] = '\0';
}

/* Get the number of a given register. */
int get_reg_num(char * reg) /* Before Opti | Before Error System */
{
    int reg_num;
    char * reg_num_str;

    reg_num_str = strchr(reg, 'r');
    reg_num_str += 1; /* Skip the 'r' */

    reg_num = str_to_int(reg_num_str);

    return reg_num;
}

/* Call this function when there is an error in the analyzer. */
void set_analyzer_error(Analyzed_line * analyzed_line, char error_content[MAX_SYTX_ERR_LENGTH])
{
    strcpy(analyzed_line->syntax_error, error_content);
}