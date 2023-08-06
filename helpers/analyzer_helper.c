#include "analyzer_helper.h"
#include <stdlib.h>
#include <string.h>

char * remove_str_quotations(char * str_content)
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

void split_operands(const char *inst_content, char *first_operand, char *second_operand) /* Before Opti | Before Error System */
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

int get_reg_num(char * reg)
{
    int reg_num;
    char * reg_num_str;

    reg_num_str = strchr(reg, 'r');
    reg_num_str += 1; /* Skip the 'r' */

    reg_num = str_to_int(reg_num_str);

    if ( 0 <= reg_num && reg_num <= 7)
        return reg_num;

    /* Invalid reg_num */
    return -1;
}