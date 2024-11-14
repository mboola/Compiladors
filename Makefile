# 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
YFLAGS = -v -d

# 
SRC_DIR = src
INPUT_DIR = tests_input
INCLUDE = include
LEXER_DIR = lexer
YACC_DIR = bison

# Source Files
SRC_FILE = ${SRC_DIR}/main.c ${SRC_DIR}/helper_functions.c

# Flex
LEX = flex
SRC_LEX = ${LEXER_DIR}/input.l
LEX_OUTPUT = lex.yy.c

# Bison
YACC = bison
SRC_YACC = ${YACC_DIR}/input.y
YACC_OUTPUT_C = input.tab.c
YACC_OUTPUT_H = input.tab.h

#
BIN = compiler_program
TEST = ${INPUT_DIR}/exe_input
VERBOSE = 
EXE_OUTPUT = result

OTHER = input.output

#
all: lex yacc
	@$(CC) $(CFLAGS) $(SRC_FILE) $(LEXER_DIR)/$(LEX_OUTPUT) ${YACC_DIR}/$(YACC_OUTPUT_C) -I $(INCLUDE) -o $(BIN)
	@echo "Compilation completed!"

lex:
	@$(LEX) -o ${LEX_OUTPUT} $(SRC_LEX)
	@mv ${LEX_OUTPUT} ${LEXER_DIR}

yacc:
	@$(YACC) $(YFLAGS) $(SRC_YACC) -H${YACC_OUTPUT_H} -o ${YACC_OUTPUT_C}
	@mv ${YACC_OUTPUT_C} ${YACC_DIR}
	@mv ${YACC_OUTPUT_H} ${INCLUDE}

test_lexer:
	ARG1 = $(shell echo $$(($(VERBOSE) + 1)))
	@./${BIN} ${ARG1} ${TEST} ${EXE_OUTPUT}

test_parser:
	ARG1 = $(shell echo $$(($(VERBOSE) + 2)))
	@./${BIN} ${ARG1} ${TEST} ${EXE_OUTPUT}

clean:
	@rm -rf $(BIN) ${LEXER_DIR}/${LEX_OUTPUT} ${YACC_DIR}/${YACC_OUTPUT_C} ${INCLUDE}/${YACC_OUTPUT_H} ${OTHER}

re: clean all
