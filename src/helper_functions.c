#include "helper_functions.h"
#include <string.h>

void *yymalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		yyerror("Malloc error");
	return (ptr);
}

void	yyerror(char *explanation)
{
	fprintf(stderr, "Error: %s , in line %d\n", explanation, yylineno);
	exit(0);
}

void	assign_expression(t_expression *exp, int type, void *value)
{
	switch (type)
	{
		case UNKNOWN_TYPE:
			break;
		case INT_TYPE:
			exp->value = yymalloc(sizeof(int));
			*((int *)exp->value) = *(int *)value;
			break;
		case FLOAT_TYPE:
			exp->value = yymalloc(sizeof(float));
			*((float *)exp->value) = *(float *)value;
			break;
		case STRING_TYPE:
			exp->value = strdup((char *)value);
			break;
		case BOOLEAN_TYPE:
			exp->value = yymalloc(sizeof(char));
			*((char *)exp->value) = *(char *)value;
			break;
	}
	exp->type = type;
}

void	print_expression(t_expression exp)
{
	switch (exp.type)
	{
		case UNKNOWN_TYPE:
			printf("Unknown type.\n");
			break;
		case INT_TYPE:
			printf("(Int type-> %d).\n", *(int *)exp.value);
			break;
		case FLOAT_TYPE:
			printf("(Float type-> %f).\n", *(float *)exp.value);
			break;
		case STRING_TYPE:
			printf("(String type-> %s).\n", (char *)exp.value);
			break;
		case BOOLEAN_TYPE:
			printf("(Bool type-> %d).\n", *(char *)exp.value);
			break;
	}
}
