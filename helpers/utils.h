#ifndef UTILS
#define UTILS

#define COMMENT_PREFIX ';'
#define MAX_LINE_LENGTH 81
#define MAX_FILE_NAME_LENGTH 200

void remove_white_spaces(char *source_line, char *dest_line);
void remove_prefix_white_spaces(char *source_line, char *dest_line);
void remove_macro_indentation(char *sourceline, char *dest_line);

#endif /* UTILS */