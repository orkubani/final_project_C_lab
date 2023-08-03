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