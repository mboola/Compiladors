#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

/*
*	Funtions used in lexer and parser.
*/

# include "data_types.h"

void	initialize_id(t_id *id, char *yytext);
void	get_id(t_id *id);
void	update_id(t_id *id);
char	*str_convert(char *yytext);
void	print_id(t_id *id);
void	print_expression(t_expression exp);
void	print_assignment(t_assignment assign);

void	initialize_expression(t_expression *exp, int type, void *value, int reg, char *lexema);
void	assign_expression(t_expression *res, t_expression exp);

#endif
