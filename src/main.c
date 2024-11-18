/*								 */
/* TODO : put here a cool header */
/*								 */

#include "helper_functions.h"
char verbose;

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
	char	*output_file;

	if (argc != 5)
	{
		dprintf(2, "ERROR: number of arguments inputed not correct.\n");
		return (0);
	}
	verbose = argv[1][0];
	execution_mode = argv[2][0];
	input_file = argv[3];
	output_file = argv[4];

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
		yyout = fopen(output_file,"r");
		if (yyout == NULL)
		{
			dprintf(2, "ERROR: parser output file could not be oppened.\n");
			return (0);
		}
		dprintf(1, "Parser started:\n");
		yyparse();
		dprintf(1, "Parser ended.\n");
		fclose(yyout);
	}
	fclose(yyin);
	return (0);
}
