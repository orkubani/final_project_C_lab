#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * Removes all white spaces from the source_line and saves the result in dest_line.
 */
void remove_white_spaces(char *source_line, char *dest_line)
{
	int i = 0;
	int j = 0;

	while (source_line[i] != '\0')
	{
		if (isspace(source_line[i]) == 0)
		{
			dest_line[j] = source_line[i];
			j++;
		}
		i++;
	}

	dest_line[j] = '\0';
}

/**
 * Removes the prefix white spaces from the source_line and saves the result in dest_line.
 */
void remove_prefix_white_spaces(char *source_line, char *dest_line)
{
    int i = 0;
    int j = 0;
    int found_first_char = 0;

    while (source_line[i] != '\0')
    {
        if (!found_first_char && isspace(source_line[i]))
        {
            i++;
            continue;
        }

        found_first_char = 1;
        dest_line[j] = source_line[i];
        i++;
        j++;
    }

    dest_line[j - 2] = '\0';
}

/**
 * Removes the macro indentation from the sourceline and saves the result in dest_line.
 * The macro indentation is assumed to start at index 4 of sourceline.
 */
void remove_macro_indentation(char *sourceline, char *dest_line)
{
    strncpy(dest_line, sourceline + FOUR_CHARS_INDENTATION, MAX_LINE_LENGTH - FOUR_CHARS_INDENTATION);
}

/* Checks if string is an int. */
int is_integer(const char *str) 
{
    char *endptr;
    strtol(str, &endptr, 10);

    return *endptr == '\0';
}

/* Covert string to int. */
int str_to_int(const char *str) 
{
    char *endptr; 
    int num;

    num = strtol(str, &endptr, 10);

    if (*endptr != '\0') 
        /* Invalid string */
        return -1;
    
    else 
        return num;
}

/* Print to the terminal a deciaml number in a binary base. */
void print_terminal_decimal_to_binary(int decimal)
{
    int binary[12];
    int i;
    int index = 0;

    if (decimal == 0)
    {
        printf("Binary: 0\n");
        return;
    }

    if (decimal < 0)
    {
        printf("Binary: ");
        decimal = (1 << 31) + decimal;
    }

    else
    {
        printf("Binary: ");
    }

    while (index < 12)
    {
        binary[index++] = decimal % 2;
        decimal /= 2;
    }

    for (i = 11; i >= 0; i--)
    {
        printf("%d", binary[i]);
    }

    printf("\n");
}

/* Print to an output file a deciaml number in a binary base. */
void print_file_decimal_to_binary(int decimal, FILE * output_file)
{
    int binary[12];
    int i;
    int index = 0;

    if (decimal == 0)
    {
        fprintf(output_file, "Binary: 0\n");
        return;
    }

    if (decimal < 0)
    {
        fprintf(output_file, "Binary: ");
        decimal = (1 << 31) + decimal;
    }

    else
    {
        fprintf(output_file, "Binary: ");
    }

    while (index < 12)
    {
        binary[index++] = decimal % 2;
        decimal /= 2;
    }

    for (i = 11; i >= 0; i--)
    {
        fprintf(output_file ,"%d", binary[i]);
    }

    fprintf(output_file, "\n");
}