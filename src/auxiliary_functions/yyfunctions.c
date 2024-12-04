/*
 *	Critical functions that define the state of the compiler
 *	or functions to show information of the state of the compiler.
 */
 
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "compiler_flags.h"

extern int yylineno;

void	yyfatal_error(char *explanation)
{
	fprintf(stderr, "%s", explanation);
	exit(0);
}

void	*yymalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		yyfatal_error("Malloc error.\n");
	return (ptr);
}

void	yyerror(char *explanation)
{
	fprintf(stderr, "%s , in line %d\n", explanation, yylineno);
	exit(0);
}

void	yylexer_error(char *explanation)
{
	fprintf(stderr, "Lexer error: ");
	yyerror(explanation);
}

void	yyparser_error(char *explanation)
{
	fprintf(stderr, "Parser error: ");
	yyerror(explanation);
}

void	yylexer_output(const char *str, ...)
{
	va_list args;

	if (lexer_verbose)
	{
		va_start(args, str);
		fprintf(output_verbose, "Lexer: ");
		vfprintf(output_verbose, str, args);
		fprintf(output_verbose, "\n");
		va_end(args);
	}
}

void	yyparser_output(const char *str, ...)
{
	va_list args;

	if (parser_verbose)
	{
		va_start(args, str);
		fprintf(output_verbose, "Parser: ");
		vfprintf(output_verbose, str, args);
		fprintf(output_verbose, "\n");
		va_end(args);
	}
}
