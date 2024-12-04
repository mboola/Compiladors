# 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
YFLAGS = -Wcounterexamples -v -d

# 
SRC_DIR = src
AUX_FUNCT_DIR = ${SRC_DIR}/auxiliary_functions
OPERATIONS_DIR = ${SRC_DIR}/operations
COMP_INST_DIR = ${SRC_DIR}/compile_instructions
INPUT_DIR = tests_input
INCLUDE = include
LEXER_DIR = lexer
YACC_DIR = bison
SYMTAB_DIR = symtab

# Source Files
AUX_FUNCT	=	${AUX_FUNCT_DIR}/helper_functions.c ${AUX_FUNCT_DIR}/yyfunctions.c \
				${AUX_FUNCT_DIR}/linked_list.c ${AUX_FUNCT_DIR}/str_functions.c \

OPERATIONS	=	${OPERATIONS_DIR}/arithmetic_operations.c ${OPERATIONS_DIR}/boolean_operations.c \
				${OPERATIONS_DIR}/repeat_operations.c ${OPERATIONS_DIR}/str_operations.c

COMP_INST	=	${COMP_INST_DIR}/compile_instructions.c

MAIN_FILES	=	${SRC_DIR}/main.c ${SRC_DIR}/compiler.c ${SRC_DIR}/compiler_flags.c

SRC_FILES	=	${AUX_FUNCT} ${OPERATIONS} ${COMP_INST} ${MAIN_FILES}

# Flex
LEX = flex
SRC_LEX = ${LEXER_DIR}/input.l
LEX_OUTPUT = lex.yy.c

# Bison
YACC = bison
SRC_YACC = ${YACC_DIR}/input.y
YACC_OUTPUT_C = input.tab.c
YACC_OUTPUT_H = input.tab.h

# Symtab
SYMTAB = ${SYMTAB_DIR}/symtab.c

#
BIN = compiler_program
TEST = ${INPUT_DIR}/exe_input
VERBOSE = 
EXE_OUTPUT = result

OTHER = input.output

#
all: symtab.o lex yacc
	@$(CC) $(CFLAGS) $(SRC_FILES) symtab.o $(LEXER_DIR)/$(LEX_OUTPUT) ${YACC_DIR}/$(YACC_OUTPUT_C) -I $(INCLUDE) -o $(BIN) -lm
	@echo "Compilation completed!"

symtab.o: ${SYMTAB}
	@${CC} ${CFLAGS} -c $< -I $(INCLUDE)

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
	@rm -rf $(BIN) ${LEXER_DIR}/${LEX_OUTPUT} ${YACC_DIR}/${YACC_OUTPUT_C} ${INCLUDE}/${YACC_OUTPUT_H} symtab.o ${OTHER}

re: clean all
