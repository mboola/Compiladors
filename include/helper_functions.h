#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

# include "data_types.h"
# include <stdio.h>
# include <stdlib.h>

extern char	lexer_verbose;
extern char	parser_verbose;

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

#endif
