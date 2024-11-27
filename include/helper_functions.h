#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

# include "data_types.h"
# include <stdio.h>
# include <stdlib.h>

# define PI_CONST 3.14159265358979323846
# define E_CONST 2.718281828459045

extern char	lexer_verbose;
extern char	parser_verbose;
extern representation_mode repmode;

extern FILE	*yyin;
extern FILE	*yyout;
extern int	yylex();
extern int	yyparse();
extern void	yyerror(char*);
extern int yylineno;

void    *yymalloc(size_t size);

//char	*type_to_str(data_type val_type);
//char	*value_info_to_str(value_info value);
void	assign_expression(t_expression *exp, int type, void *value);
void	yyerror(char *explanation);

char	*str_convert(char *yytext);

void	initialize_id(t_id *id, char *yytext);
void	get_id(t_id *id);
void	print_id(t_id *id);
void	update_id(t_id *id);

void	print_expression(t_expression exp);
void	print_assignment(t_assignment assign);

// Arithmetic operations
void	addition(t_expression *result, t_expression first_exp, t_expression second_exp);
void	substraction(t_expression *result, t_expression first_exp, t_expression second_exp);
void	multiplication(t_expression *result, t_expression first_exp, t_expression second_exp);
void	division(t_expression *result, t_expression first_exp, t_expression second_exp);
void	modulation(t_expression *result, t_expression first_exp, t_expression second_exp);
void	power(t_expression *result, t_expression first_exp, t_expression second_exp);

void	sin_funct(t_expression *result, t_expression exp);
void	cos_funct(t_expression *result, t_expression exp);
void	tan_funct(t_expression *result, t_expression exp);

// Boolean operations
void	or(t_expression *result, t_expression first_exp, t_expression second_exp);
void	and(t_expression *result, t_expression first_exp, t_expression second_exp);
void	not(t_expression *result, t_expression exp);
void	compare(t_expression *result, t_expression first_exp, t_oprel oprel, t_expression second_exp);

void	my_strlen(t_expression *result, t_expression exp);

#endif
