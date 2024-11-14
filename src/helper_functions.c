#include "helper_functions.h"
#include <string.h>

char	*expression_to_str(t_expression expr)
{
	char buffer[STR_MAX_LENGTH];

	if (expr.type == UNKNOWN_TYPE)
		sprintf(buffer, "Unknown expr type");
	else if (expr.type == INT_TYPE)
		sprintf(buffer, "Integer: %d", *(int *)expr.value);
	else if (expr.type == FLOAT_TYPE)
		sprintf(buffer, "Float: %f", *(float *)expr.value);
	else
		sprintf(buffer, "Error: incorrect expr for 'expr.type'");
	return strdup(buffer);
}

char    *assignment_to_str(t_assignment assign)
{
	char buffer[STR_MAX_LENGTH];

	sprintf(buffer, "Name: %s ", assign.name);
	return strdup(buffer);
}

void	yyerror(char *explanation)
{
	fprintf(stderr, "Error: %s , in line %d\n", explanation, yylineno);
}
