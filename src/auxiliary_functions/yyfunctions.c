/*
 *	Critical functions that define the state of the compiler
 *	or functions to show information of the state of the compiler.
 */
 
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "compiler_flags.h"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

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
	fprintf(stderr, "%s, in line %d:%d.\n", explanation, yylineno, yycol);
	exit(0);
}

/*
 *	Only called when an error in the lexer is found and I want to
 *	display all the line. Will get called when program ends.
 */
static char	*get_current_line(FILE *file)
{
	static char	line_buffer[1024];
	int			current_line;

	current_line = 1;
	fseek(file, 0, SEEK_SET);
	while (fgets(line_buffer, sizeof(line_buffer), file))
	{
		if (current_line == yylineno)
			break;
		current_line++;
	}
	return line_buffer;
}

void	yylexer_error()
{
	fprintf(stderr, "Lexer error: in line %d:%d -> ", yylineno, yycol);
	fprintf(stderr, "Unidentified token '%s'.\n", yytext),
	fprintf(stderr, "Line: %s", get_current_line(yyin));
	exit(0);
}

void	yyparser_error(char *explanation)
{
	fprintf(stderr, "Parser error: in line %d:%d -> ", yylineno, yycol);
	fprintf(stderr, "%s\n", explanation);
	fprintf(stderr, "Line: %s", get_current_line(yyin));
	exit(0);
}

void	update_yycol()
{
	yycol += strlen(yytext);
}

void	yylexer_output(const char *str, ...)
{
	va_list args;

	update_yycol();
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
