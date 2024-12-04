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

static char	*get_register(int reg)
{
	return (strjoin("$t", convert_int_to_str(reg)));
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
		str = strjoin(str, get_register(exp.reg));
	add_instruction(str, -1);
	current_reg = 1 + 2 * regs_reserved;
}

static char	*get_curr_reg()
{
	char	*str;

	str = convert_int_to_str(current_reg);
	str = strjoin("$t0", str);
	current_reg++;
	return (str);
}

static char	*get_reg(t_expression *exp)
{
	if (exp->reg == 0)
	{
		if (exp->lexema != NULL)
			return (strdup(exp->lexema));
		else
		{
			if (exp->type == INT_TYPE)
				return (convert_int_to_str(*(int *)exp->value));
			else
				return (convert_float_to_str(*(float *)exp->value));
		}
	}
	return (strjoin("$t0", convert_int_to_str(exp->reg)));
}

void	compile_int_to_float(t_expression *exp)
{
	char	*str;
	int		reg;

	reg = current_reg;
	str = get_curr_reg();
	str = strjoin(str, " := I2F ");
	str = strjoin(str, get_reg(exp));
	exp->reg = reg;
	add_instruction(str, -1);
}

void	compile_arithmetic_expression(t_expression first_exp, t_expression second_exp, char *operation, t_expression *res)
{
	char	*str;
	int		reg;

	if (first_exp.type != second_exp.type)
	{
		if (first_exp.type == INT_TYPE)
			compile_int_to_float(&first_exp);
		else
			compile_int_to_float(&second_exp);
		reg = current_reg;
		str = strjoin(get_curr_reg(), " := ");
		str = strjoin(str, get_reg(&first_exp));
		str = strjoin(str, " ");
		str = strjoin(str, operation);
		str = strjoin(str, "F ");
		str = strjoin(str, get_reg(&second_exp));
	}
	else
	{
		reg = current_reg;
		str = strjoin(get_curr_reg(), " := ");
		str = strjoin(str, get_reg(&first_exp));
		str = strjoin(str, " ");
		str = strjoin(str, operation);
		if (first_exp.type == INT_TYPE)
			str = strjoin(str, "I ");
		else
			str = strjoin(str, "F ");
		str = strjoin(str, get_reg(&second_exp));
	}
	add_instruction(str, -1);
	res->reg = reg;
}
