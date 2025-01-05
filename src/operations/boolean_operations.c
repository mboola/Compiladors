#include "yyfunctions.h"
#include "data_types.h"
#include "compile_instructions.h"
#include "compiler.h"

void	or(t_expression *result, t_expression first_exp, int curr_line, t_expression second_exp)
{
	fill_list(first_exp.false_list, curr_line); // TODO : NOT SURE if to use instructions_inputed
	result->true_list = join_list(&(first_exp.true_list), second_exp.true_list);
	result->false_list = second_exp.false_list;

	result->value = yymalloc(sizeof(char *));
	if (*((char *)first_exp.value) == 1)
		*((char *)result->value) = 1;
	else if (*((char *)second_exp.value) == 1)
		*((char *)result->value) = 1;
	else
		*((char *)result->value) = 0;
}

void	and(t_expression *result, t_expression first_exp, int curr_line, t_expression second_exp)
{
	fill_list(first_exp.true_list, curr_line); // TODO : NOT SURE if to use instructions_inputed
	result->true_list = join_list(&(first_exp.false_list), second_exp.false_list);
	result->true_list = second_exp.true_list;

	result->value = yymalloc(sizeof(char *));
	if (*(char *)first_exp.value == 0)
		*((char *)result->value) = 0;
	else if (*(char *)second_exp.value == 0)
		*((char *)result->value) = 0;
	else
		*((char *)result->value) = 1;
}

void	not(t_expression *result, t_expression exp)
{
	result->false_list = exp.true_list;
	result->true_list = exp.false_list;

	result->type = exp.type;
	result->value = yymalloc(sizeof(char *));
	*((char *)result->value) = !*(char *)exp.value;
}

void	compare(t_expression *result, t_expression first_exp, t_oprel oprel, t_expression second_exp)
{
	float	value;
	char	both_ints;

	if (first_exp.type == UNKNOWN_TYPE || second_exp.type == UNKNOWN_TYPE)
		yyparser_error("Cannot compare uninitialized expressions.");
	if (first_exp.type == STRING_TYPE || second_exp.type == STRING_TYPE)
		yyparser_error("Cannot compare STRING_TYPE expressions.");
	if (first_exp.type == BOOLEAN_TYPE || second_exp.type == BOOLEAN_TYPE)
		yyparser_error("Cannot compare BOOLEAN_TYPE expressions.");

	both_ints = 0;
	if (first_exp.type == INT_TYPE && second_exp.type == INT_TYPE)
		both_ints = 1;
	// TODO : convert to same type instruction I2F or F2I...
	else if (first_exp.type == INT_TYPE && second_exp.type == FLOAT_TYPE)
		value = *(int *)first_exp.value;
	else if (second_exp.type == INT_TYPE && first_exp.type == FLOAT_TYPE)
		value = *(int *)second_exp.value;

	result->type = BOOLEAN_TYPE;
	result->value = yymalloc(sizeof(char));

	switch (oprel.type)
	{
		case LESEQ:
			if (both_ints)
				*((char *)result->value) = (*(int *)first_exp.value <= *(int *)second_exp.value);
			else if (first_exp.type == INT_TYPE)
				*((char *)result->value) = value <= *(float *)second_exp.value;
			else if (second_exp.type == INT_TYPE)
				*((char *)result->value) = *(float *)first_exp.value <= value;
			else
				*((char *)result->value)  = (*(float *)first_exp.value <= *(float *)second_exp.value);
			break;
		case BIGEQ:
			if (both_ints)
				*((char *)result->value) = (*(int *)first_exp.value >= *(int *)second_exp.value);
			else if (first_exp.type == INT_TYPE)
				*((char *)result->value) = value >= *(float *)second_exp.value;
			else if (second_exp.type == INT_TYPE)
				*((char *)result->value) = *(float *)first_exp.value >= value;
			else
				*((char *)result->value)  = (*(float *)first_exp.value >= *(float *)second_exp.value);
			break;
		case NOTEQ:
			if (both_ints)
				*((char *)result->value) = (*(int *)first_exp.value != *(int *)second_exp.value);
			else if (first_exp.type == INT_TYPE)
				*((char *)result->value) = value != *(float *)second_exp.value;
			else if (second_exp.type == INT_TYPE)
				*((char *)result->value) = *(float *)first_exp.value != value;
			else
				*((char *)result->value)  = (*(float *)first_exp.value != *(float *)second_exp.value);
			break;
		case LESSER:
			if (both_ints)
				*((char *)result->value) = (*(int *)first_exp.value < *(int *)second_exp.value);
			else if (first_exp.type == INT_TYPE)
				*((char *)result->value) = (value < *(float *)second_exp.value);
			else if (second_exp.type == INT_TYPE)
				*((char *)result->value) = *(float *)first_exp.value < value;
			else
				*((char *)result->value)  = (*(float *)first_exp.value < *(float *)second_exp.value);
			break;
		case BIGGER:
			if (both_ints)
				*((char *)result->value) = (*(int *)first_exp.value > *(int *)second_exp.value);
			else if (first_exp.type == INT_TYPE)
				*((char *)result->value) = value > *(float *)second_exp.value;
			else if (second_exp.type == INT_TYPE)
				*((char *)result->value) = *(float *)first_exp.value > value;
			else
				*((char *)result->value)  = (*(float *)first_exp.value > *(float *)second_exp.value);
			break;
		case EQUAL:
			if (both_ints)
				*((char *)result->value) = (*(int *)first_exp.value == *(int *)second_exp.value);
			else if (first_exp.type == INT_TYPE)
				*((char *)result->value) = value == *(float *)second_exp.value;
			else if (second_exp.type == INT_TYPE)
				*((char *)result->value) = *(float *)first_exp.value == value;
			else
				*((char *)result->value)  = (*(float *)first_exp.value == *(float *)second_exp.value);
			break;
	}
	compile_compare(result, first_exp, oprel, second_exp);
}
