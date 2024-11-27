#include "helper_functions.h"

static void	print_line()
{
	fprintf(yyc3a_output, "%d: ", n_line);
	n_line++;
}

static void	convert_value(data_type type, void *value)
{
	switch (type)
	{
		case UNKNOWN_TYPE:
			yyerror("Cannot convert an unknown value");
			break;
		case INT_TYPE:
			fprintf(yyc3a_output, "%d", *(int *)value);
			break;
		case FLOAT_TYPE:
			fprintf(yyc3a_output, "%f", *(float *)value);
			break;
		case STRING_TYPE:
			fprintf(yyc3a_output, "%s", (char *)value);
			break;
		case BOOLEAN_TYPE:
			fprintf(yyc3a_output, "%d", *(int *)value);
			break;
	}
}

void	convert_assignation(t_id id, t_expression exp)
{
	print_line();
	fprintf(yyc3a_output, "%s := ", id.lexema);

	// If there has not been an assignation we print the value of exp
	if (n_register == -1)
		convert_value(exp.type, exp.value);
	fprintf(yyc3a_output, "\n");
}
