#include "helper_functions.h"

void	and()
{

}

void	or()
{

}

void	not()
{

}

void	compare(t_expression *result, t_expression first_exp, t_oprel oprel, t_expression second_exp)
{
	if (first_exp.type != second_exp.type)
		yyerror("Cannot compare two different types.");
	if (first_exp.type == UNKNOWN_TYPE || second_exp.type == UNKNOWN_TYPE)
		yyerror("Cannot compare uninitialized expressions.");
	if (first_exp.type == STRING_TYPE || second_exp.type == STRING_TYPE)
		yyerror("Cannot compare STRING_TYPE expressions.");
	if (first_exp.type == BOOLEAN_TYPE || second_exp.type == BOOLEAN_TYPE)
		yyerror("Cannot compare BOOLEAN_TYPE expressions.");
	result->type = BOOLEAN_TYPE;
	switch (oprel.type)
	{
		case LESEQ:
			if (first_exp.type == INT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value) = (*(int *)first_exp.value <= *(int *)second_exp.value);
				return ;
			}
			if (first_exp.type == FLOAT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(float *)first_exp.value <= *(float *)second_exp.value);
				return ;
			}
			break;
		case BIGEQ:
			if (first_exp.type == INT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(int *)first_exp.value >= *(int *)second_exp.value);
				return ;
			}
			if (first_exp.type == FLOAT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(float *)first_exp.value >= *(float *)second_exp.value);
				return ;
			}
			break;
		case NOTEQ:
			if (first_exp.type == INT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(int *)first_exp.value != *(int *)second_exp.value);
				return ;
			}
			if (first_exp.type == FLOAT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(float *)first_exp.value != *(float *)second_exp.value);
				return ;
			}
			break;
		case LESSER:
			if (first_exp.type == INT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(int *)first_exp.value < *(int *)second_exp.value);
				return ;
			}
			if (first_exp.type == FLOAT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(float *)first_exp.value < *(float *)second_exp.value);
				return ;
			}
			break;
		case BIGGER:
			if (first_exp.type == INT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(int *)first_exp.value > *(int *)second_exp.value);
				return ;
			}
			if (first_exp.type == FLOAT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(float *)first_exp.value > *(float *)second_exp.value);
				return ;
			}
			break;
		case EQUAL:
			if (first_exp.type == INT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(int *)first_exp.value == *(int *)second_exp.value);
				return ;
			}
			if (first_exp.type == FLOAT_TYPE)
			{
				result->value = yymalloc(sizeof(char));
				*((char *)result->value)  = (*(float *)first_exp.value == *(float *)second_exp.value);
				return ;
			}
			break;
	}
}
