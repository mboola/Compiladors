#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

# include <stdio.h>
# include <stdlib.h>
# include "data_types.h"

char	*expression_to_str(t_expression expr);
char    *assignment_to_str(t_assignment assign);
void	yyerror(char *explanation);

#endif
