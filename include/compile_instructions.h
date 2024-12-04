#ifndef COMPILE_INSTRUCTIONS_H
# define COMPILE_INSTRUCTIONS_H

void	compile_assignation(t_id id, t_expression exp);
void	compile_arithmetic_expression(t_expression first_exp, t_expression second_exp, char *operation, t_expression *res);
void	compile_expression(t_expression exp);
#endif
