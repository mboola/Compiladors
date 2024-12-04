#include "data_types.h"
#include "yyfunctions.h"
#include "str_functions.h"
#include "compiler.h"

void	handle_repeat_start(t_repeat *rep, t_expression exp)
{
	if (exp.type != INT_TYPE)
		yyerror("Type of expresion to repeat not correct. Must be INT_TYPE.");
	if (*(int *)exp.value < 0)
		yyerror("Iteration negative not possible");
	// Before entering here, exp must have generated an instruction with a register $tXX.
	// We must store in rep->inst the following:
	//		IF $tXX+1 LTI $tXX GOTO line
	// We initialize a reg with the value 0. This reg will be used to 
	// check ending of repeat and store somewhere next line
	//add_instruction(rep.instruction, -1);
	// Here we must store inside rep the condition. This condition will be outputed
	// in handle_repeat_loop, stored in repstart
	rep->instruction = strdup("testing");
}

void	handle_repeat_loop(t_repeat repstart)
{
	// Here we will add repstart->inst as an instruction
	add_instruction(repstart.instruction, -1);
}
