#include "helper_functions.h"
#include <string.h>

void	initialize_id(t_id *id, char *yytext)
{
	t_id	*id_to_search;

	if (sym_lookup(yytext, &id_to_search) == SYMTAB_NOT_FOUND)
	{
		id->lexema = strdup(yytext);
		id->type = UNKNOWN_TYPE;
		id->value = NULL;
		sym_add(id->lexema, &id);
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

void	addition(t_expression *result, t_expression first_exp, t_expression second_exp)
{
	switch (first_exp.type)
	{
		case INT_TYPE:
			if (second_exp.type == INT_TYPE)
			{
				result->type = INT_TYPE;
				*(int *)(result->value) = *(int *)first_exp.value + *(int *)second_exp.value;
			}
			break;
		case UNKNOWN_TYPE:
		case FLOAT_TYPE:
		case STRING_TYPE:
		case BOOLEAN_TYPE:
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
}
