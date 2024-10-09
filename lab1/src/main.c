/*								 */
/* TODO : put here a cool header */
/*								 */

#include "helper_functions.h"
char verbose;

int	main(int argc, char **argv)
{
	verbose = 1;
	if (argc < 2)
	{
		dprintf(2, "ERROR: input not correct.\n");
		return (0);
	}
	yyin = fopen(argv[1],"r");
	if (yyin == NULL)
	{
		dprintf(2, "ERROR: input file could not be oppened.\n");
		return (0);
	}
	dprintf(1, "Lexer started:\n");
	yylex();
	dprintf(1, "Lexer ended:\n");
	fclose(yyin);
	yyout = fopen(argv[2],"r");
	if (yyout == NULL)
	{
		dprintf(2, "ERROR: input file could not be oppened.\n");
		return (0);
	}
	dprintf(1, "Parser started:\n");
	yyparse();
	dprintf(1, "Parser ended:\n");
	fclose(yyout);
	return (0);
}
