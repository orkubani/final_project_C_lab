#ifndef FIRST_MOVE_H
#define FIRST_MOVE_H

typedef struct Compiled_Inst /* Code section */
{
    unsigned int inst_word;
    unsigned int first_extra_word;
    unsigned int second_extra_word;
    int num_of_words;
    struct Compiled_Inst *next_inst;
}Compiled_Inst;

typedef struct Compiled_Dir /* Data section */
{
    /* Implement struct here */
    struct Compiled_Dir *next_dir;
}Compiled_Dir;


typedef struct Extern_Calls 
{
    /* Implement struct here */
}Extern_Calls;


typedef struct Entries_Calls 
{
    /* Implement struct here */
}Entries_Calls;

#endif /*  */