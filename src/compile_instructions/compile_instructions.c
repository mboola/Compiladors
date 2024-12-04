#include "yyfunctions.h"
#include "str_functions.h"
#include "compiler.h"
#include "data_types.h"

static char	*convert_int_to_str(int i)
{
	char num[12]; //MAX NEGATIVE INT 11 chars + '\0'

	sprintf(num, "%d", i);
	return (strdup(num));
}

static char	*convert_float_to_str(float f)
{
	char num[15]; //MAX FLOAT 14 chars + '\0'

	sprintf(num, "%e", f);
	return (strdup(num));
}

static char	*convert_bool_to_str(int b)
{
	char num[2];

	sprintf(num, "%d", b);
	return (strdup(num));
}

static char *convert_value(data_type type, void *value)
{
	if (type == UNKNOWN_TYPE)
		yyerror("Cannot convert an unknown value");
	if (type == INT_TYPE)
		return(convert_int_to_str(*(int *)value));
	if (type == FLOAT_TYPE)
		return (convert_float_to_str(*(float *)value));
	if (type == STRING_TYPE)
		return (strdup((char *)value)); // not sure if duplication is needed.
	return (convert_bool_to_str(*(int *)value));
}

static char	*join_register(char *str, int reg)
{
	str = strjoin(str, "$t");
	return (strjoin(str, convert_int_to_str(reg)));
}

/*
 *	Converts an assignation into an instruction in c3a
 */
void	compile_assignation(t_id id, t_expression exp)
{
	char	*str;

	str = strjoin(id.lexema, " := ");
	if (exp.reg == 0)
		str = strjoin(str, convert_value(exp.type, exp.value));
	else
		str = join_register(str, exp.reg);
	add_instruction(str, -1);
}
