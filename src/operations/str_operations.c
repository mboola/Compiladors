#include "str_functions.h"
#include "yyfunctions.h"
#include "data_types.h"

void	my_strlen(t_expression *result, t_expression exp)
{
	if (exp.type != STRING_TYPE)
		yyerror("Cannot strlen with a type not equivalent to STRING_TYPE."); // TODO : change this
	result->type = INT_TYPE;
	result->value = yymalloc(sizeof(int));
	*(int *)result->value = strlen((char *)exp.value);
}

void	my_substr(t_expression *result, t_expression exp1, t_expression exp2, t_expression exp3)
{
	if (exp1.type != STRING_TYPE)
		yyerror("Cannot substr with the first operand type not equivalent to STRING_TYPE."); // TODO : change this
	if (exp2.type != INT_TYPE)
		yyerror("Cannot substr with the second operand type not equivalent to INT_TYPE."); // TODO : change this
	if (exp3.type != INT_TYPE)
		yyerror("Cannot substr with the third operand type not equivalent to INT_TYPE."); // TODO : change this
	result->value = substr((char *)exp1.value, *(int *)exp2.value, (*(int *)exp3.value + 1));
	result->type = STRING_TYPE;
}
