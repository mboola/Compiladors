#include "data_types.h"
#include "yyfunctions.h"
#include "str_functions.h"
#include "compiler.h"
#include "str_functions.h"

static char	*convert_int_to_str(int i)
{
	char num[12]; //MAX NEGATIVE INT 11 chars + '\0'

	sprintf(num, "%d", i);
	return (strdup(num));
}

void	handle_repeat_start(t_repeat *rep, t_expression exp)
{
	char	*str;

	if (exp.type != INT_TYPE)
		yyerror("Type of expresion to repeat not correct. Must be INT_TYPE.");
	if (*(int *)exp.value < 0)
		yyerror("Iteration negative not possible");
	if (exp.reg > (2 * regs_reserved + 1))
	{
		// get last reg of exp
		str = strjoin("$t0", convert_int_to_str(exp.reg));
		str = strjoin(" := ", str);
		str = strjoin(convert_int_to_str(1 + 2 * regs_reserved), str);
		str = strjoin("$t0", str);
		add_instruction(str, -1);
		current_reg = 1 + 2 * (regs_reserved + 1);
	}
	// Initialize $t(1 + regs_reserved * 2 + 1) to 0
	str = strjoin("$t0", convert_int_to_str(1 + regs_reserved * 2 + 1));
	str = strjoin(str, " := 0");
	add_instruction(str, -1);
	print_all_instructions();

	// Here we are in the line we must store
	// $t(1 + regs_reserved * 2 + 1) := $t(1 + regs_reserved * 2 + 1) ADDI 1
	str = strjoin("$t0", convert_int_to_str(1 + regs_reserved * 2 + 1));
	str = strjoin(str, " := $t0");
	str = strjoin(str, convert_int_to_str(1 + regs_reserved * 2 + 1));
	str = strjoin(str, " ADDI 1");
	rep->update = str;

	// IF $t0(1 + regs_reserved * 2 + 1) LTI $t0(1 + regs_reserved * 2) GOTO curr_line
	str = strjoin("IF $t0", convert_int_to_str(1 + regs_reserved * 2 + 1));
	str = strjoin(str, " LTI $t0");
	str = strjoin(str, convert_int_to_str(1 + regs_reserved * 2));
	str = strjoin(str, " GOTO ");
	str = strjoin(str, convert_int_to_str(line));
	rep->jump = str;

	// Here we have the regs 1 + regs_reserved * 2 and 1 + regs_reserved * 2 + 1 reserved to this loop
	regs_reserved++;
	current_reg = 1 + 2 * regs_reserved;
}

void	handle_repeat_loop(t_repeat repstart)
{
	// Here we will add repstart->inst as an instruction
	add_instruction(repstart.update, -1);
	add_instruction(repstart.jump, -1);
}
