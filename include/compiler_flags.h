#ifndef COMPILER_FLAGS_H
# define COMPILER_FLAGS_H

// FILE * definition
# include <stdio.h>

typedef enum {
	BIN_MODE,
	OCT_MODE,
	DEC_MODE,
	HEX_MODE
}	representation_mode;

extern char	lexer_verbose;
extern char	parser_verbose;
extern representation_mode repmode;
extern FILE *output_verbose;

#endif
