#include "helper_functions.h"
#include <string.h>
#include <math.h>

static char	*strjoin(const char *str1, const char *str2)
{
	char *dst;
	
	dst = yymalloc(strlen(str1) + strlen(str2) + 1);
	strcpy(dst, str1);
	strcat(dst, str2);
	return dst;
}

void	addition(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
				*(int *)(result->value) = *(int *)first_exp.value + *(int *)second_exp.value;
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
				yyerror("Cannot add INT_TYPE with FLOAT_TYPE.\n");
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = *(float *)first_exp.value + *(float *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
			{
				char str[50];
				sprintf(str, "%f", *(float *)first_exp.value);
				result->value = strjoin(strdup(str), (char *)second_exp.value);
			}
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot add FLOAT_TYPE with UNKNOWN_TYPE.\n");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot add FLOAT_TYPE with BOOLEAN_TYPE.\n");
			else if (second_exp.type == INT_TYPE)
				yyerror("Cannot add FLOAT_TYPE with INT_TYPE.\n");
			result->type = second_exp.type;
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
				*(int *)(result->value) = *(int *)first_exp.value - *(int *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot substract INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot substract INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot substract INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
				yyerror("Cannot substract INT_TYPE with FLOAT_TYPE.");
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = *(float *)first_exp.value - *(float *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
				yyerror("Cannot substract FLOAT_TYPE with INT_TYPE.");
			result->type = second_exp.type;
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
				*(int *)(result->value) = *(int *)first_exp.value * *(int *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
				yyerror("Cannot multiplicate INT_TYPE with FLOAT_TYPE.");
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = *(float *)first_exp.value * *(float *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
				yyerror("Cannot multiplicate FLOAT_TYPE with INT_TYPE.");
			result->type = second_exp.type;
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
				*(int *)(result->value) = *(int *)first_exp.value / *(int *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot divide INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot divide INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot divide INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
				yyerror("Cannot divide INT_TYPE with FLOAT_TYPE.");
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = *(float *)first_exp.value / *(float *)second_exp.value;
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with INT_TYPE.");
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

void	modulation(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
				*(int *)(result->value) = *(int *)first_exp.value % *(int *)second_exp.value;
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

static int	powi(int i, int j)
{
	int	result;

	if (i < 0 || j < 0)
		return 0;
	result = i;
	for (int k = 0; k < j; k++)
	{
		result = result * j;
	}
	return result;
}

void	power(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
				*(int *)(result->value) = powi(*(int *)first_exp.value, *(int *)second_exp.value);
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot divide INT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot divide INT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot divide INT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == FLOAT_TYPE)
				yyerror("Cannot divide INT_TYPE with FLOAT_TYPE.");
			result->type = second_exp.type;
			break;
		case FLOAT_TYPE:
			if (second_exp.type == FLOAT_TYPE)
				*(float *)(result->value) = powf(*(float *)first_exp.value, *(float *)second_exp.value);
			else if (second_exp.type == STRING_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with STRING_TYPE.");
			else if (second_exp.type == UNKNOWN_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with UNKNOWN_TYPE.");
			else if (second_exp.type == BOOLEAN_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with BOOLEAN_TYPE.");
			else if (second_exp.type == INT_TYPE)
				yyerror("Cannot divide FLOAT_TYPE with INT_TYPE.");
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
