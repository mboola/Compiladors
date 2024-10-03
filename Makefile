# 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

# 
SRC_DIR = src
INPUT_DIR = input
INCLUDE = include
LEXER_DIR = lexer

SRC_FILE = ${SRC_DIR}/main.c

#
LEX = flex
SRC_LEX = ${LEXER_DIR}/input.l
LEX_OUTPUT = lex.yy.c

#
BIN = executable
EXE_INPUT = ${INPUT_DIR}/exe_input.txt


#
all: lex
	@$(CC) $(CFLAGS) $(SRC_FILE) $(SRC_EXTRA) $(LEX_OUT) -I ${INCLUDE} -o $(BIN)

lex: $(SRC_LEX)
	@$(LEX) -o ${LEX_OUTPUT} $(SRC_LEX)
	@mv ${LEX_OUTPUT} ${LEXER_DIR}

test_lex: all
	@./$(BIN) $(EXE_INPUT)

clean:
	@rm -rf $(BIN) ${LEXER_DIR}/${LEX_OUTPUT}

re: clean all
