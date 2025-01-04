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
 *	Recieves seven arguments:
 *	First: Lexer verbose mode.
 *	Second: Parser verbose mode.
 *	Third: Mode of execution: execute only lexer or parser and lexer.
 *	Fourth: Input file.
 *	Fifth: Output file.
 *	Sixth: Calculator result file.
 *	Seventh: Compiled file.
 */
int	main(int argc, char **argv)
{
	char	execution_mode;
	char	*input_file;
	char	*verbose_result;
	char	*calc_result;
	char	*compiled_file;

	if (argc != 8)
		yyfatal_error("ERROR: number of arguments inputed not correct.\n");

	repmode = DEC_MODE;
	lexer_verbose = atoi(argv[1]);
	parser_verbose = atoi(argv[2]);
	execution_mode = atoi(argv[3]);
	input_file = argv[4];
	verbose_result = argv[5];
	calc_result = argv[6];
	compiled_file = argv[7];

	yycol = 0;
	
	yyin = fopen(input_file, "r");
	if (yyin == NULL)
		yyfatal_error("ERROR: input file could not be opened.\n");

	output_verbose = fopen(verbose_result, "w");
	if (output_verbose == NULL)
	{
		fclose(yyin);
		yyfatal_error("ERROR: verbose result could not be opened.\n");
	}

	output_result = fopen(calc_result, "w");
	if (output_result == NULL)
	{
		fclose(yyin);
		fclose(output_verbose);
		yyfatal_error("ERROR: calculator result could not be opened.\n");
	}

	if (execution_mode)
	{
		dprintf(1, "Lexer started:\n");
		while (yylex());
		dprintf(1, "Lexer ended.\n");
	}
	else
	{
		// Open file to output instructions. Compiled file.
		if (open_output_file(compiled_file))
		{
			fclose(yyin);
			fclose(output_verbose);
			fclose(output_result);
			yyfatal_error("ERROR: result compilation file could not be opened.\n");
		}

		dprintf(1, "Parser started:\n");
		yyparse();
		dprintf(1, "Parser ended.\n");

		close_output_file();
	}
	fclose(yyin);
	fclose(output_verbose);
	fclose(output_result);
	return (0);
}
