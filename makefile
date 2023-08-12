CC			= gcc
CFLAGS		= -ansi -pedantic -Wall
PROG_NAME	= main
BUILD_DIR 	= build
OBJ_DIR 	= $(BUILD_DIR)/obj
BIN_DIR		= $(BUILD_DIR)/bin

ifdef DEBUG
CFLAGS += -g
endif

.PHONY: clean build_dir all

all: build_dir $(PROG_NAME)

$(PROG_NAME): build_dir main.o preprocessor.o macro_table.o utils.o analyzer_helper.o analyzer.o compiled_line.o assembler_helper.o first_move.o symbol_table.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/$@

main.o: main.c preprocessor/preprocessor.h preprocessor/macro_table.h \
 preprocessor/../helpers/utils.h assembler/first_move.h
preprocessor.o: preprocessor/preprocessor.c preprocessor/preprocessor.h \
 preprocessor/macro_table.h preprocessor/../helpers/utils.h
macro_table.o: preprocessor/macro_table.c preprocessor/macro_table.h \
 preprocessor/../helpers/utils.h
utils.o: helpers/utils.c helpers/utils.h
analyzer_helper.o: helpers/analyzer_helper.c helpers/analyzer_helper.h
analyzer.o: analyzer/analyzer.c analyzer/analyzer.h \
 analyzer/../helpers/utils.h analyzer/../helpers/analyzer_helper.h
compiled_line.o: data_structures/compiled_line.c data_structures/compiled_line.h
assembler_helper.o: helpers/assembler_helper.c helpers/assembler_helper.h 
symbol_table.o: data_structures/symbol_table.c data_structures/symbol_table.h
first_move.o: assembler/first_move.c assembler/first_move.h \
 assembler/../helpers/utils.h assembler/../helpers/analyzer_helper.h \
 assembler/../analyzer/analyzer.h assembler/../data_structures/compiled_line.h assembler/../helpers/assembler_helper.h \
 assembler/../data_structures/symbol_table.h

%.o:
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)

build_dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
