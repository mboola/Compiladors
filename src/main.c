/*								 */
/* TODO : put here a cool header */
/*								 */

#include "compiler.h"
#include "compiler_flags.h"
#include "yyfunctions.h"
#include <stdio.h>
#include <stdlib.h>

extern int	yylex();
extern int	yyparse();
extern FILE *yyin;

/*
 *	Recieves three arguments:
 *	First: Lexer verbose mode.
 *	Second: Parser verbose mode.
 *	Third: Mode of execution: execute only lexer or parser and lexer.
 *	Fourth: Input file.
 *	Fifth: Output file.
 *	Sixth: Compiled file.
 */
int	main(int argc, char **argv)
{
	char	execution_mode;
	char	*input_file;
	char	*verbose_result;
	char	*compiled_file;

	if (argc != 7)
		yyfatal_error("ERROR: number of arguments inputed not correct.\n");

	repmode = DEC_MODE;
	lexer_verbose = atoi(argv[1]);
	parser_verbose = atoi(argv[2]);
	execution_mode = atoi(argv[3]);
	input_file = argv[4];
	verbose_result = argv[5];
	compiled_file = argv[6];

	yyin = fopen(input_file, "r");
	if (yyin == NULL)
		yyfatal_error("ERROR: input file could not be opened.\n");
	if (execution_mode == '1')
	{
		dprintf(1, "Lexer started:\n");
		while (yylex());
		dprintf(1, "Lexer ended.\n");
	}
	else
	{
		output_verbose = fopen(verbose_result,"w");
		if (output_verbose == NULL)
			yyfatal_error("ERROR: verbose result could not be opened.\n");
		if (open_output_file(compiled_file))
		{
			fclose(output_verbose);
			yyfatal_error("ERROR: result compilation file could not be opened.\n");
		}
		dprintf(1, "Parser started:\n");
		yyparse();
		dprintf(1, "Parser ended.\n");
		close_output_file();
		fclose(output_verbose);
	}
	fclose(yyin);
	return (0);
}
