#ifndef PARSER_OPERATIONS_H
# define PARSER_OPERATIONS_H

# include "data_types.h"

// Arithmetic operations
void	addition(t_expression *result, t_expression first_exp, t_expression second_exp);
void	substraction(t_expression *result, t_expression first_exp, t_expression second_exp);
void	negate(t_expression *result, t_expression exp);
void	multiplication(t_expression *result, t_expression first_exp, t_expression second_exp);
void	division(t_expression *result, t_expression first_exp, t_expression second_exp);
void	modulation(t_expression *result, t_expression first_exp, t_expression second_exp);
void	power(t_expression *result, t_expression first_exp, t_expression second_exp);

void	sin_funct(t_expression *result, t_expression exp);
void	cos_funct(t_expression *result, t_expression exp);
void	tan_funct(t_expression *result, t_expression exp);

// Repeat operations
void	handle_repeat_start(t_repeat *rep, t_expression exp);
void	handle_repeat_loop(t_repeat repstart);

#endif
