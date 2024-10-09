# 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
YFLAGS = -v -d

# 
SRC_DIR = src
INPUT_DIR = input
INCLUDE = include
LEXER_DIR = lexer
YACC_DIR = bison

# Source Files
SRC_FILE = ${SRC_DIR}/main.c ${SRC_DIR}/exemple_funcions.c ${SRC_DIR}/exemple_dades.c

# Flex
LEX = flex
SRC_LEX = ${LEXER_DIR}/input.l
LEX_OUTPUT = lex.yy.c

# Bison
YACC = bison
SRC_YACC = ${YACC_DIR}/input.y
YACC_OUTPUT_C = input.tab.c
YACC_OUTPUT_H = input.tab.h
YACC_OUTPUT = yacc.output

#
BIN = compiler_program
EXE_INPUT = ${INPUT_DIR}/exe_input
EXE_OUTPUT = exe_output

#
all: lex yacc
	@$(CC) $(CFLAGS) $(SRC_FILE) $(LEXER_DIR)/$(LEX_OUTPUT) ${YACC_DIR}/$(YACC_OUTPUT_C) -I $(INCLUDE) -o $(BIN)
	@echo "Compilation completed!"
	@echo "->Now you can execute with ./${BIN} [test_name] [exe_output]"

lex:
	@$(LEX) -o ${LEX_OUTPUT} $(SRC_LEX)
	@mv ${LEX_OUTPUT} ${LEXER_DIR}

yacc : $(SRC_YACC)
	$(YACC) $(YFLAGS) $(SRC_YACC) -H${YACC_OUTPUT_H} -o ${YACC_OUTPUT_C}
	@mv ${YACC_OUTPUT_C} ${YACC_DIR}
	@mv ${YACC_OUTPUT_H} ${INCLUDE}

clean:
	@rm -rf $(BIN) ${LEXER_DIR}/${LEX_OUTPUT} ${YACC_DIR}/${YACC_OUTPUT_C} ${YACC_DIR}/${YACC_OUTPUT_H} ${OTHER}

re: clean all
