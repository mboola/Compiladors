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

	sprintf(num, "%.1f", f);
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
	return (strjoin("$t0", convert_int_to_str(reg)));
}

char	*get_exp_register(t_expression exp)
{
	if (exp.reg == 0)
		return convert_value(exp.type, exp.value);
	return get_register(exp.reg);
}

/*
 *	Converts an assignation into an instruction in c3a
 */
void	compile_assignation(t_id id, t_expression exp)
{
	char	*str;

	str = strjoin(id.lexema, " := ");
	str = strjoin(str, get_exp_register(exp));
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

void	compile_power(t_expression first_exp, t_expression second_exp, t_expression *res)
{
	int	exponent;
	char int_type = 1;
	int last_reg;
	char	*str;

	// If base is float we must convert it to int.
	if (first_exp.type != INT_TYPE)
		int_type = 0;

	if (second_exp.type == INT_TYPE)
		exponent = *(int *)second_exp.value;
	else
		exponent = (int) *(float *)second_exp.value; //round exponent

	// first iteration
	// $0xx = first_exp->lex MULTX first_exp->lex
	// last_reg = $0xx
	last_reg = current_reg;
	str = strjoin(get_curr_reg(), " := ");
	str = strjoin(str, get_reg(&first_exp));
	if (int_type)
		str = strjoin(str, " MULI ");
	else
		str = strjoin(str, " MULF ");
	str = strjoin(str, get_reg(&first_exp));
	add_instruction(str, -1);

	for (int i = 2; i < exponent; i++)
	{
		str = strjoin(get_curr_reg(), " := ");
		str = strjoin(str, get_register(last_reg));
		last_reg++;
		if (int_type)
			str = strjoin(str, " MULI ");
		else
			str = strjoin(str, " MULF ");
		str = strjoin(str, get_reg(&first_exp));
		add_instruction(str, -1);
	}
	// add last reg to result->reg
	res->reg = last_reg;
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
		str = strjoin(get_curr_reg(), " := "); // result reg
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

void	compile_expression(t_expression exp)
{
	char	*str;

	if (exp.lexema == NULL)
		yyparser_error("Statement with no effect");
	str = strjoin("PARAM ", exp.lexema);
	add_instruction(str, -1);
	if (exp.type == INT_TYPE)
		str = strdup("CALL PUTI, 1");
	else if (exp.type == FLOAT_TYPE)
		str = strdup("CALL PUTF, 1");
	else if (exp.type == STRING_TYPE)
		str = strdup("CALL PUTS, 1");
	else if (exp.type == UNKNOWN_TYPE)
		yyparser_error("Cannot print uninitialized value");
	add_instruction(str, -1);
}

static int	get_current_position()
{
	return instructions_inputed;
}

void	compile_compare(t_expression *result, t_expression first_exp, t_oprel oprel, t_expression second_exp)
{
	char	*instruction;

	instruction = strjoin("IF ", get_reg(&first_exp));

	switch (oprel.type)
	{
		case LESEQ:
			instruction = strjoin(instruction, " LE");
			break;
		case BIGEQ:
			instruction = strjoin(instruction, " GE");
			break;
		case NOTEQ:
			instruction = strjoin(instruction, " NE");
			break;
		case LESSER:
			instruction = strjoin(instruction, " LT");
			break;
		case BIGGER:
			instruction = strjoin(instruction, " GT");
			break;
		case EQUAL:
			instruction = strjoin(instruction, " EQ");
			break;
	}
	if (first_exp.type == INT_TYPE)
		instruction = strjoin(instruction, "I ");
	else
		instruction = strjoin(instruction, "F ");
	instruction = strjoin(instruction, get_reg(&second_exp));
	instruction = strjoin(instruction, " GOTO ");

	int pos = get_current_position();

	result->true_list = create_list(pos);
	result->false_list = create_list(pos + 1);

	add_instruction(instruction, -1);
	add_instruction(strdup("GOTO "), -1);
}
