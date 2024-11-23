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

/*
 *	Only called in input.l when ID_TKN found.
 */
void	initialize_id(t_id *id, char *yytext)
{
	t_id	*id_to_search;

	if (sym_lookup(yytext, &id_to_search) == SYMTAB_NOT_FOUND)
	{
		id_to_search = yymalloc(sizeof(t_id));
		id_to_search->lexema = strdup(yytext);
		id_to_search->type = UNKNOWN_TYPE;
		id_to_search->value = NULL;
		sym_add(id_to_search->lexema, &id_to_search);
	}
	id->lexema = id_to_search->lexema;
	id->type = id_to_search->type;
	id->value = id_to_search->value;
}

void	get_id(t_id *id)
{
	t_id	*id_to_search;

	if (sym_lookup(id->lexema, &id_to_search) == SYMTAB_NOT_FOUND)
		yyerror("UNEXPECTED ERROR id not found in symtab."); // Something must have gone wrong, it should exist inside
	id->lexema = id_to_search->lexema;
	id->type = id_to_search->type;
	id->value = id_to_search->value;
}

void	update_id(t_id *id)
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
		//cpyid(id_to_search, id);
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

void	print_assignment(t_assignment assign)
{
	t_id *id_to_search;

	if (sym_lookup(assign.name, &id_to_search) == SYMTAB_NOT_FOUND)
		yyerror("Id not found when printing an assignation.");
	else
		print_id(id_to_search);
}

void	yyerror(char *explanation)
{
	fprintf(stderr, "Error: %s , in line %d\n", explanation, yylineno);
	exit(0);
}
