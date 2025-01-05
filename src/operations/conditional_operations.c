#include "compiler.h"
#include "data_types.h"
#include "string.h"
#include "str_functions.h"

static char	*convert_int_to_str(int i)
{
	char num[12]; //MAX NEGATIVE INT 11 chars + '\0'

	sprintf(num, "%d", i);
	return (strdup(num));
}

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
	if_start->true_section_line = instructions_inputed; // TODO : change for nested ifs
}

void	end_if(t_if if_start)
{
	int	false_section_line;

	false_section_line = if_start.true_section_line + lstsize(instructions);

	// recover instructions before if
	lstadd_back(&if_start.instructions, instructions);
	instructions = if_start.instructions;

	// goto true is current_line in file + offset gotos
	fill_list(if_start.expression.true_list, if_start.true_section_line);
	// goto false is current_line in file + offset gotos + len(instrucions)
	fill_list(if_start.expression.false_list, false_section_line);
}

void	initialize_while(t_while *while_start)
{
	while_start->current_instructions = instructions_inputed;
}

void	update_while(t_while *while_to_update, t_while while_start, t_expression boolean_expression)
{
	// TODO : if boolean expression is false maybe dont do anything?

	// store to while_to_update all the instructions before this
	while_to_update->instructions = instructions;

	// reset instructions
	instructions = NULL;

	/* here inside boolean_expression we have the gotos instructions */
	/* some instructions will have a dir to goto and some wont */
	while_to_update->expression = boolean_expression;

	// true goto is current line + boolean conditionals
	while_to_update->true_section_line = instructions_inputed;

	while_to_update->current_instructions = instructions_inputed - while_start.current_instructions;
}

void	end_while(t_while while_start)
{
	int	false_section_line;
	char	*final_jump_instruction;

	false_section_line = while_start.true_section_line + lstsize(instructions);

	// recover instructions before if
	lstadd_back(&while_start.instructions, instructions);
	instructions = while_start.instructions;

	// goto true is current_line in file + offset gotos
	fill_list(while_start.expression.true_list, while_start.true_section_line);
	// goto false is current_line in file + offset gotos + len(instrucions)
	fill_list(while_start.expression.false_list, false_section_line + 1);

	// Add final jump instruction
	final_jump_instruction = strjoin("GOTO ", convert_int_to_str(while_start.true_section_line - while_start.current_instructions));
	add_instruction(final_jump_instruction, -1);
}
