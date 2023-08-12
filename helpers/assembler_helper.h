#ifndef ASSEMBLER_HELPER_H
#define ASSEMBLER_HELPER_H

#include "../assembler/first_move.h"

/**
 * @brief Set extra word for instruction based on the operand type.
 * 
 * @param analyzed_line analyzed_line to check the operand_type.
 * @param compiled_line to write the extra word to.
 * @param operand_i operand dest/src.
 */
void set_inst_extra_words(Analyzed_line analyzed_line, Compiled_Line * compiled_line, int num_of_operands);

#endif /* ASSEMBLER_HELPER_H */