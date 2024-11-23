#include "helper_functions.h"
#include <string.h>

void	initialize_id(t_id *id, char *yytext)
{
	t_id	*id_to_search;

	if (sym_lookup(yytext, &id_to_search) == SYMTAB_NOT_FOUND)
	{
		id_to_search = malloc(sizeof(t_id));
		id_to_search->lexema = strdup(yytext);
		id_to_search->type = UNKNOWN_TYPE;
		id_to_search->value = NULL;
		id->lexema = id_to_search->lexema;
		id->type = id_to_search->type;
		id->value = id_to_search->value;
		sym_add(id_to_search->lexema, &id_to_search);
	}
	else
	{
		id->lexema = id_to_search->lexema;
		id->type = id_to_search->type;
		id->value = id_to_search->value;
	}
}

void	get_id(t_id *id)
{
	t_id	*id_to_search;
	if (sym_lookup(id->lexema, &id_to_search) == SYMTAB_NOT_FOUND)
	{
		// Something must have gone wrong, it should exist inside
		printf("ERROR\n");
		exit(0);
	}
	else
	{
		id->lexema = id_to_search->lexema;
		id->type = id_to_search->type;
		id->value = id_to_search->value;
	}
}

void	update_id(t_id *id)
{
	t_id	*id_to_search;
	printf("Searching %s\n", id->lexema);
	if (sym_lookup(id->lexema, &id_to_search) == SYMTAB_NOT_FOUND)
	{
		// Something must have gone wrong, it should exist inside
		printf("ERROR\n");
		exit(0);
	}
	else
	{
		id_to_search->lexema = id->lexema;
		id_to_search->type = id->type;
		id_to_search->value = id->value;
	}
}

void	print_id(t_id *id)
{
	printf("Printing id %s: ", id->lexema);
	switch (id->type)
	{
		case UNKNOWN_TYPE:
			printf("Unknown type.\n");
			break;
		case INT_TYPE:
			printf("(Int type-> %d).\n", *(int *)id->value);
			break;
		case FLOAT_TYPE:
			printf("(Float type-> %f).\n", *(float *)id->value);
			break;
		case STRING_TYPE:
			printf("(String type-> %s).\n", (char *)id->value);
			break;
		case BOOLEAN_TYPE:
			printf("(Bool type-> %d).\n", *(char *)id->value);
			break;
	}
}

void	print_expression(t_expression *exp)
{
	switch (exp->type)
	{
		case UNKNOWN_TYPE:
			printf("Unknown type.\n");
			break;
		case INT_TYPE:
			printf("(Int type-> %d).\n", *(int *)exp->value);
			break;
		case FLOAT_TYPE:
			printf("(Float type-> %f).\n", *(float *)exp->value);
			break;
		case STRING_TYPE:
			printf("(String type-> %s).\n", (char *)exp->value);
			break;
		case BOOLEAN_TYPE:
			printf("(Bool type-> %d).\n", *(char *)exp->value);
			break;
	}
}

static char	*strjoin(const char *str1, const char *str2)
{
	char *dst = malloc(strlen(str1) + strlen(str2) + 1);
	if (dst)
	{
		strcpy(dst, str1);
		strcat(dst, str2);
	}
	return dst;
}

void	addition(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	print_expression(&first_exp);
	print_expression(&second_exp);
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
			else
				yyerror("Operation type not supported.\n");
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
			else
				yyerror("Operation type not supported.\n");
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
			else
				yyerror("Operation type not supported.\n");
			result->type = STRING_TYPE;
			break;
		case BOOLEAN_TYPE:
		case UNKNOWN_TYPE:
			yyerror("Operation type not supported4.\n");
			break;
	}
}

void	assign_expression(t_expression *exp, int type, void *value)
{
	exp->type = type;
	exp->value = value;
}

void	yyerror(char *explanation)
{
	fprintf(stderr, "Error: %s , in line %d\n", explanation, yylineno);
	exit(0);
}
