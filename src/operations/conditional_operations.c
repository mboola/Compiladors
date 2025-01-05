#include "compiler.h"
#include "data_types.h"

void	initialize_if(t_if *if_start, t_expression boolean_expression)
{
	// store to if_start all the instructions before this
    if_start->instructions = instructions;

    // reset instructions
    instructions = NULL;

    /* here inside boolean_expression we have the gotos instructions */
    /* some instructions will have a dir to goto and some wont */
    if_start->expression = boolean_expression;

	// true goto is current line + boolean conditionals
	if_start->true_section_line = line + lstsize(if_start->instructions); // TODO : change for nested ifs
}

void	end_if(t_if if_start)
{
	// goto true is current_line in file + offset gotos
	fill_list(if_start.expression.true_list, if_start.true_section_line);
	
	// goto false is current_line in file + offset gotos + len(instrucions)
	fill_list(if_start.expression.false_list, if_start.true_section_line + lstsize(if_start.instructions));

    // last: recover instructions before if
    instructions = if_start.instructions;
}
