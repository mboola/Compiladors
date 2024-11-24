#include "helper_functions.h"
#include "symtab.h"
#include <string.h>

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
			switch (repmode)
			{
				case BIN_MODE:
					printf("(Int type-> %d).\n", *(int *)id->value);
					break;
				case OCT_MODE:
					printf("(Int type-> %o).\n", *(int *)id->value);
					break;
				case DEC_MODE:
					printf("(Int type-> %d).\n", *(int *)id->value);
					break;
				case HEX_MODE:
					printf("(Int type-> %x).\n", *(int *)id->value);
					break;
			}
			break;
		case FLOAT_TYPE:
			switch (repmode)
			{
				case BIN_MODE:
					printf("(Float type-> %f).\n", *(float *)id->value);
					break;
				case OCT_MODE:
					printf("(Float type-> %f).\n", *(float *)id->value);
					break;
				case DEC_MODE:
					printf("(Float type-> %f).\n", *(float *)id->value);
					break;
				case HEX_MODE:
					printf("(Float type-> %f).\n", *(float *)id->value);
					break;
			}
			break;
		case STRING_TYPE:
			printf("(String type-> %s).\n", (char *)id->value);
			break;
		case BOOLEAN_TYPE:
			printf("(Bool type-> %d).\n", *(char *)id->value);
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
