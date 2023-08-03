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

$(PROG_NAME): build_dir main.o preprocessor.o macro_table.o utils.o analyzer_helper.o analyzer.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/$@

main.o: main.c preprocessor/preprocessor.h preprocessor/macro_table.h \
 preprocessor/../helpers/utils.h
preprocessor.o: preprocessor/preprocessor.c preprocessor/preprocessor.h \
 preprocessor/macro_table.h preprocessor/../helpers/utils.h
macro_table.o: preprocessor/macro_table.c preprocessor/macro_table.h \
 preprocessor/../helpers/utils.h
utils.o: helpers/utils.c helpers/utils.h
analyzer_helper.o: helpers/analyzer_helper.c helpers/analyzer_helper.h
analyzer.o: analyzer/analyzer.c analyzer/analyzer.h \
 analyzer/../helpers/utils.h analyzer/../helpers/analyzer_helper.h

%.o:
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)

build_dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
