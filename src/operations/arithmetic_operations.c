#include "yyfunctions.h"
#include "data_types.h"
#include "str_functions.h"
#include "compile_instructions.h"
#include <math.h>

void	addition(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "ADD", result);
				*(int *)(result->value) = (*(int *)first_exp.value) + (*(int *)second_exp.value);
			}
			else if (second_exp.type == STRING_TYPE)
			{
				char str[12];
				sprintf(str, "%d", *(int *)first_exp.value);
				result->value = strjoin(strdup(str), (char *)second_exp.value);
			}
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot add INT_TYPE with UNKNOWN_TYPE.\n");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot add INT_TYPE with BOOLEAN_TYPE.\n");
			else if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "ADD", result);
				*(float *)(result->value) = *(int *)first_exp.value + *(float *)second_exp.value;
			}
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "ADD", result);
				*(float *)(result->value) = *(float *)first_exp.value + *(float *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
			{
				char str[50];
				sprintf(str, "%f", *(float *)first_exp.value);
				result->value = strjoin(strdup(str), (char *)second_exp.value);
				result->type = second_exp.type;
				return ;
			}
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot add FLOAT_TYPE with UNKNOWN_TYPE.\n");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot add FLOAT_TYPE with BOOLEAN_TYPE.\n");
			else if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "ADD", result);
				*(float *)(result->value) = *(float *)first_exp.value + *(int *)second_exp.value;
			}
			result->type = first_exp.type;
			break;
		case STRING_TYPE: // Always concatenate
			if (second_exp.type == STRING_TYPE)
				result->value = strjoin((char *)first_exp.value, (char *)second_exp.value);
			else if (second_exp.type == INT_TYPE)
			{
				char str[12];
				sprintf(str, "%d", *(int *)second_exp.value);
				result->value = strjoin((char *)first_exp.value, strdup(str));
			}
			else if (second_exp.type == FLOAT_TYPE)
			{
				char str[50];
				sprintf(str, "%f", *(float *)second_exp.value);
				result->value = strjoin((char *)first_exp.value, strdup(str));
			}
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot add STRING_TYPE with UNKNOWN_TYPE.\n");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot add STRING_TYPE with BOOLEAN_TYPE.\n");
			result->type = STRING_TYPE;
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot add: First operator has BOOLEAN_TYPE.");
			break;
		case UNKNOWN_TYPE:
			yyerror("Cannot add: First operator has UNKNOWN_TYPE.");
			break;
	}
}

void	substraction(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "SUB", result);
				*(int *)(result->value) = *(int *)first_exp.value - *(int *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot substract INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot substract INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot substract INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "SUB", result);
				*(float *)(result->value) = *(int *)first_exp.value - *(float *)second_exp.value;
			}
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "SUB", result);
				*(float *)(result->value) = *(float *)first_exp.value - *(float *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "SUB", result);
				*(float *)(result->value) = *(float *)first_exp.value - *(int *)second_exp.value;
			}
			result->type = first_exp.type;
			break;
		case STRING_TYPE:
			yyerror("Cannot substract: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot substract: First operator has BOOLEAN_TYPE.");
			break;
		case UNKNOWN_TYPE:
			yyerror("Cannot substract: First operator has UNKNOWN_TYPE.");
			break;
	}
}

void	multiplication(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "MUL", result);
				*(int *)(result->value) = *(int *)first_exp.value * *(int *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "MUL", result);
				*(float *)(result->value) = *(int *)first_exp.value * *(float *)second_exp.value;
			}
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "MUL", result);
				*(float *)(result->value) = *(float *)first_exp.value * *(float *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "MUL", result);
				*(float *)(result->value) = *(float *)first_exp.value * *(int *)second_exp.value;
			}
			result->type = first_exp.type;
			break;
		case STRING_TYPE:
			yyerror("Cannot multiplicate: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot multiplicate: First operator has BOOLEAN_TYPE.");
			break;
		case UNKNOWN_TYPE:
			yyerror("Cannot multiplicate: First operator has UNKNOWN_TYPE.");
			break;
	}
}

void	division(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "DIV", result);
				*(int *)(result->value) = *(int *)first_exp.value / *(int *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot divide INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot divide INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot divide INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "DIV", result);
				*(int *)(result->value) = *(int *)first_exp.value / *(float *)second_exp.value;
			}
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "DIV", result);
				*(float *)(result->value) = *(float *)first_exp.value / *(float *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "DIV", result);
				*(float *)(result->value) = *(float *)first_exp.value / *(int *)second_exp.value;
			}
			result->type = first_exp.type;
			break;
		case STRING_TYPE:
			yyerror("Cannot divide: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot divide: First operator has BOOLEAN_TYPE.");
			break;
		case UNKNOWN_TYPE:
			yyerror("Cannot divide: First operator has UNKNOWN_TYPE.");
			break;
	}
}

void	modulation(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
			{
				compile_arithmetic_expression(first_exp, second_exp, "MOD", result);
				*(int *)(result->value) = *(int *)first_exp.value % *(int *)second_exp.value;
			}
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot modulate INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot modulate INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot modulate INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
				yyerror("Cannot modulate INT_TYPE with FLOAT_TYPE.");
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			yyerror("Cannot modulate: First operator has FLOAT_TYPE.");
			break;
		case STRING_TYPE:
			yyerror("Cannot modulate: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot modulate: First operator has BOOLEAN_TYPE.");
			break;
		case UNKNOWN_TYPE:
			yyerror("Cannot modulate: First operator has UNKNOWN_TYPE.");
			break;
	}
}

void	power(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
				*(int *)(result->value) = powf((float)*(int *)first_exp.value, (float)*(int *)second_exp.value);
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot pow INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot pow INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot pow INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = powf((float)*(int *)first_exp.value, *(float *)second_exp.value);
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = powf(*(float *)first_exp.value, *(float *)second_exp.value);
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot pow FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot pow FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot pow FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
				*(float *)(result->value) = powf(*(float *)first_exp.value, *(float *)second_exp.value);
			result->type = second_exp.type;
			break;
		case STRING_TYPE:
			yyerror("Cannot divide: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot divide: First operator has BOOLEAN_TYPE.");
			break;
		case UNKNOWN_TYPE:
			yyerror("Cannot divide: First operator has UNKNOWN_TYPE.");
			break;
	}
}

void	sin_funct(t_expression *result, t_expression exp)
{
	result->type = FLOAT_TYPE;
	result->value = yymalloc(sizeof(float));
	switch (exp.type)
	{
		case UNKNOWN_TYPE:
			yyerror("Cannot operate: unitialized value.");
			break;
		case INT_TYPE:
			*((float *)result->value) = sin(*((int *)exp.value));
			break;
		case FLOAT_TYPE:
			*((float *)result->value) = sin(*((float *)exp.value));
			break;
		case STRING_TYPE:
			yyerror("Cannot divide: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot divide: First operator has BOOLEAN_TYPE.");
			break;
	}
}

void	cos_funct(t_expression *result, t_expression exp)
{
	result->type = FLOAT_TYPE;
	result->value = yymalloc(sizeof(float));
	switch (exp.type)
	{
		case UNKNOWN_TYPE:
			yyerror("Cannot operate: unitialized value.");
			break;
		case INT_TYPE:
			*((float *)result->value) = cos(*((int *)exp.value));
			break;
		case FLOAT_TYPE:
			*((float *)result->value) = cos(*((float *)exp.value));
			break;
		case STRING_TYPE:
			yyerror("Cannot divide: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot divide: First operator has BOOLEAN_TYPE.");
			break;
	}
}

void	tan_funct(t_expression *result, t_expression exp)
{
	result->type = FLOAT_TYPE;
	result->value = yymalloc(sizeof(float));
	switch (exp.type)
	{
		case UNKNOWN_TYPE:
			yyerror("Cannot operate: unitialized value.");
			break;
		case INT_TYPE:
			*((float *)result->value) = tan(*((int *)exp.value));
			break;
		case FLOAT_TYPE:
			*((float *)result->value) = tan(*((float *)exp.value));
			break;
		case STRING_TYPE:
			yyerror("Cannot divide: First operator has STRING_TYPE.");
			break;
		case BOOLEAN_TYPE:
			yyerror("Cannot divide: First operator has BOOLEAN_TYPE.");
			break;
	}
}
