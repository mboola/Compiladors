#ifndef PARSER_OPERATIONS_H
# define PARSER_OPERATIONS_H

# include "data_types.h"

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

// String operations
void	my_strlen(t_expression *result, t_expression exp);
void	my_substr(t_expression *result, t_expression exp1, t_expression exp2, t_expression exp3);

// Repeat operations
void	handle_repeat_start(t_repeat *rep, t_expression exp);
void	handle_repeat_loop(t_repeat repstart);

#endif
