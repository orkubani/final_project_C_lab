#include "utils.h"
#include <stdio.h>
#include <ctype.h>

void remove_white_spaces(char *line)
{
    char *src = line;
    char *dst = line;

    while (*src != '\0') 
    {
        if (!isspace(*src)) 
        {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';
}
