#include "compiler_flags.h"
#include "data_types.h"
#include "str_functions.h"
#include "yyfunctions.h"
#include "symtab.h"

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
		yyfatal_error("UNEXPECTED ERROR id not found in symtab."); // Something must have gone wrong, it should exist inside
	id->lexema = id_to_search->lexema;
	id->type = id_to_search->type;
	id->value = id_to_search->value;
}

void	update_id(t_id *id)
{
	t_id	*id_to_search;

	if (sym_lookup(id->lexema, &id_to_search) == SYMTAB_NOT_FOUND)
		yyfatal_error("UNEXPECTED ERROR id not found in symtab."); // Something must have gone wrong, it should exist inside
	else
	{
		id_to_search->lexema = id->lexema;
		id_to_search->type = id->type;
		id_to_search->value = id->value;
	}
}

// Converts a "str" into a str. removes double quotes
char	*str_convert(char *yytext)
{
	*(yytext + strlen(yytext) - 1) = '\0';
	return strdup(++yytext);
}

// used to print a value inside the output_verbose file
static void	print_value(data_type type, void *value)
{
	switch (type)
	{
		case UNKNOWN_TYPE:
			fprintf(output_verbose, "Unknown type."); // TODO : whatehell
			break;
		case INT_TYPE:
			switch (repmode)
			{
				case BIN_MODE:
					fprintf(output_verbose, "(Int type-> %d).", *(int *)value);
					break;
				case OCT_MODE:
					fprintf(output_verbose, "(Int type-> %o).", *(int *)value);
					break;
				case DEC_MODE:
					fprintf(output_verbose, "(Int type-> %d).", *(int *)value);
					break;
				case HEX_MODE:
					fprintf(output_verbose, "(Int type-> %x).", *(int *)value);
					break;
			}
			break;
		case FLOAT_TYPE: // TODO : create functions to represent different types of floats
			switch (repmode)
			{
				case BIN_MODE:
					fprintf(output_verbose, "(Float type-> %f).", *(float *)value);
					break;
				case OCT_MODE:
					fprintf(output_verbose, "(Float type-> %f).", *(float *)value);
					break;
				case DEC_MODE:
					fprintf(output_verbose, "(Float type-> %f).", *(float *)value);
					break;
				case HEX_MODE:
					fprintf(output_verbose, "(Float type-> %f).", *(float *)value);
					break;
			}
			break;
		case STRING_TYPE:
			fprintf(output_verbose, "(String type-> %s).", (char *)value);
			break;
		case BOOLEAN_TYPE:
			fprintf(output_verbose, "(Bool type-> %d).", *(char *)value);
			break;
	}
}

void	print_id(t_id *id)
{
	fprintf(output_verbose, "Printing id %s: ", id->lexema);
	print_value(id->type, id->value);
	fprintf(output_verbose, "\n");
}

void	print_expression(t_expression exp)
{
	fprintf(output_verbose, "Printing expression: ");
	print_value(exp.type, exp.value);
	fprintf(output_verbose, "\n");
}

void	print_assignment(t_assignment assign)
{
	t_id *id_to_search;

	if (sym_lookup(assign.name, &id_to_search) == SYMTAB_NOT_FOUND)
		yyfatal_error("Id not found when printing an assignation.");
	else
		print_id(id_to_search);
}

void	assign_expression(t_expression *exp, int type, void *value, int reg, char *lexema)
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
	exp->reg = reg;
	exp->lexema = lexema;
}
