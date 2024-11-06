#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# include <stdio.h>

# define STR_MAX_LENGTH 200

extern char	verbose;
extern FILE	*yyin;
extern FILE	*yyout;
extern int	yylex();
extern int	yyparse();
extern void	yyerror(char*);
extern int yylineno;

typedef enum {
	UNKNOWN_TYPE = 1,
	INT_TYPE,
	FLOAT_TYPE,
	STRING_TYPE,
	BOOLEAN_TYPE
}	expression_type;


typedef struct {
	expression_type	type;
	void			*value;
}	expression;

typedef struct {
	char			*name;
	expression_type	type;
	void			*value;
}	assignment;

typedef struct {
	char *lexema;
	int length;
	int line;
}	id;


#endif
