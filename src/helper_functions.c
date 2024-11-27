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

char	*str_convert(char *yytext)
{
	*(yytext + strlen(yytext) - 1) = '\0';
	return strdup(++yytext);
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
			switch (repmode)
			{
				case BIN_MODE:
					printf("(Int type-> %d).\n", *(int *)exp.value);
					break;
				case OCT_MODE:
					printf("(Int type-> %o).\n", *(int *)exp.value);
					break;
				case DEC_MODE:
					printf("(Int type-> %d).\n", *(int *)exp.value);
					break;
				case HEX_MODE:
					printf("(Int type-> %x).\n", *(int *)exp.value);
					break;
			}
			break;
		case FLOAT_TYPE:
			switch (repmode)
			{
				case BIN_MODE:
					printf("(Float type-> %f).\n", *(float *)exp.value);
					break;
				case OCT_MODE:
					printf("(Float type-> %f).\n", *(float *)exp.value);
					break;
				case DEC_MODE:
					printf("(Float type-> %f).\n", *(float *)exp.value);
					break;
				case HEX_MODE:
					printf("(Float type-> %f).\n", *(float *)exp.value);
					break;
			}
			break;
		case STRING_TYPE:
			printf("(String type-> %s).\n", (char *)exp.value);
			break;
		case BOOLEAN_TYPE:
			printf("(Bool type-> %d).\n", *(char *)exp.value);
			break;
	}
}

void	my_strlen(t_expression *result, t_expression exp)
{
	if (exp.type != STRING_TYPE)
		yyerror("Cannot strlen with a type not equivalent to STRING_TYPE."); // TODO : change this
	result->type = INT_TYPE;
	result->value = yymalloc(sizeof(int));
	*(int *)result->value = strlen((char *)exp.value);
}

static int	strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	size;

	size = strlen(src);
	if (dstsize == 0)
		return (size);
	i = 0;
	while (*(src + i) != '\0' && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (size);
}


static char	*substr(char const *s, int start, int len)
{
	char	*str;
	int	s_len;
	int	size;

	if (s == NULL)
		size = 1;
	else
	{
		s_len = strlen(s);
		if (start > s_len)
			size = 1;
		else if (len > s_len - start)
			size = s_len - start + 1;
		else
			size = len + 1;
	}
	str = yymalloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (start > s_len)
		*str = '\0';
	else
		strlcpy(str, s + start, len);
	return (str);
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
