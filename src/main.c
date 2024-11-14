/*								 */
/* TODO : put here a cool header */
/*								 */

#include "helper_functions.h"
char verbose;

/*
 *	Recieves three arguments:
 *	First: Verbose mode.
 *	Second: Mode of execution.
 *	Third: Lexer input file.
 *	Fourth: Parser output file.
 */
int	main(int argc, char **argv)
{
	char	execution_mode;
	char	*lexer_file;
	char	*parser_file;

	if (argc != 5)
	{
		dprintf(2, "ERROR: number of arguments inputed not correct.\n");
		return (0);
	}
	verbose = argv[1][0];
	execution_mode = argv[2][0];
	lexer_file = argv[3];
	parser_file = argv[4];

	yyin = fopen(lexer_file, "r");
	if (yyin == NULL)
	{
		dprintf(2, "ERROR: lexer input file could not be oppened.\n");
		return (0);
	}
	dprintf(1, "Lexer started:\n");
	yylex();
	dprintf(1, "Lexer ended.\n");
	fclose(yyin);

	// If I'm only testing lexer we leave
	if (execution_mode == '1')
		return (0);

	yyout = fopen(parser_file,"r");
	if (yyout == NULL)
	{
		dprintf(2, "ERROR: parser output file could not be oppened.\n");
		return (0);
	}
	dprintf(1, "Parser started:\n");
	yyparse();
	dprintf(1, "Parser ended.\n");
	fclose(yyout);
	return (0);
}
