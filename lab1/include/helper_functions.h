#ifndef HELPER_FUNCTIONS_H
# define HELPER_FUNCTIONS_H
 
# include <stdio.h>
# include <stdlib.h>

extern char	verbose;
extern FILE *yyin;
extern FILE *yyout;
extern int yylex();
extern int yyparse();

#endif