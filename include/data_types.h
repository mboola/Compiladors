#ifndef DATA_TYPES_H
# define DATA_TYPES_H

#define STR_MAX_LENGTH 200

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
	FLOAT_TYPE
}	data_type;


typedef struct {
	data_type val_type;
	int val_int;
	float val_float;
}	value_info;


#endif
