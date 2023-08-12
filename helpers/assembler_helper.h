#ifndef ASSEMBLER_HELPER_H
#define ASSEMBLER_HELPER_H

#include "../assembler/assembler.h"

/**
 * @brief Set extra word for instruction based on the operand type.
 * 
 * @param analyzed_line analyzed_line to check the operand_type.
 * @param compiled_line to write the extra word to.
 * @param operand_i operand dest/src.
 */
void set_inst_extra_words(Analyzed_line analyzed_line, Compiled_Line * compiled_line, int num_of_operands);

/**
 * @brief Generate assembler warning.
 * 
 * @param line_index The line where is the warning.
 */
void assembler_warning(int line_index);


/**
 * @brief Generate assembler error.
 * 
 * @param line_index The line where is the error.
 */
void assembler_error(int line_index);

#endif /* ASSEMBLER_HELPER_H */