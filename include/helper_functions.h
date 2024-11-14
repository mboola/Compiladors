#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

# include <stdio.h>
# include <stdlib.h>
# include "data_types.h"

char	*type_to_str(data_type val_type);
char	*value_info_to_str(value_info value);
void	yyerror(char *explanation);

#endif
