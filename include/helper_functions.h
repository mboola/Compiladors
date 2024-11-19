#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H

# include <stdio.h>
# include <stdlib.h>
# include "data_types.h"

extern char	verbose;
extern FILE	*yyin;
extern FILE	*yyout;
extern int	yylex();
extern int	yyparse();
extern void	yyerror(char*);
extern int yylineno;

//char	*type_to_str(data_type val_type);
//char	*value_info_to_str(value_info value);
void	yyerror(char *explanation);

#endif
