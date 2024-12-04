#ifndef YYFUNCTIONS_H
# define YYFUNCTIONS_H

// size_t definition 
# include <stdio.h>

void	yyfatal_error(char *explanation);
void	*yymalloc(size_t size);
void	yyerror(char *explanation);
void	yylexer_error(char *explanation);
void	yyparser_error(char *explanation);
void	yylexer_output(const char *str, ...);
void	yyparser_output(const char *str, ...);

#endif
