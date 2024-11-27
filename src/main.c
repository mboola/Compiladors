/*								 */
/* TODO : put here a cool header */
/*								 */

#include "helper_functions.h"
char	lexer_verbose;
char	parser_verbose;
representation_mode repmode;

FILE	*yyfrontend_res;
FILE	*yyc3a_output;

/*
 *	Recieves three arguments:
 *	First: Verbose mode.
 *	Second: Mode of execution.
 *	Third: Input file.
 *	Fourth: Output file.
 */
int	main(int argc, char **argv)
{
	char	execution_mode;
	char	*input_file;
	char	*frontend_result;
	char	*c3a_output;

	if (argc != 7)
	{
		dprintf(2, "ERROR: number of arguments inputed not correct.\n");
		return (0);
	}
	repmode = DEC_MODE;
	lexer_verbose = atoi(argv[1]);
	parser_verbose = atoi(argv[2]);
	execution_mode = atoi(argv[3]);
	input_file = argv[4];
	frontend_result = argv[5];
	c3a_output = argv[6];

	n_register = -1;
	n_line = 1;

	yyin = fopen(input_file, "r");
	if (yyin == NULL)
	{
		dprintf(2, "ERROR: input file could not be oppened.\n");
		return (0);
	}
	if (execution_mode == '1')
	{
		dprintf(1, "Lexer started:\n");
		while (yylex());
		dprintf(1, "Lexer ended.\n");
	}
	else
	{
		yyfrontend_res = fopen(frontend_result,"w");
		yyc3a_output = fopen(c3a_output,"w");
		if (yyfrontend_res == NULL)
		{
			dprintf(2, "ERROR: parser output file could not be oppened.\n");
			return (0);
		}
		dprintf(1, "Parser started:\n");
		yyparse();
		dprintf(1, "Parser ended.\n");
		fclose(yyc3a_output);
		fclose(yyfrontend_res);
	}
	fclose(yyin);
	return (0);
}
