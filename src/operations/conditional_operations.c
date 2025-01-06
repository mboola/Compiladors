#include "compiler.h"
#include "data_types.h"
#include "string.h"
#include "str_functions.h"
#include "yyfunctions.h"
#include "compile_instructions.h"
#include "helper_functions.h"

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
	if_start->true_section_line = instructions_inputed;
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

void	initialize_else(t_if *if_else, t_if if_start)
{
	if_else->node_goto = create_list(instructions_inputed);
	add_instruction(strdup("GOTO "), -1);
	
	if_else->false_section_line = instructions_inputed;
	if_else->instructions = if_start.instructions;
	if_else->expression = if_start.expression;
}

void	end_else(t_if if_else)
{
	// recover instructions before if
	lstadd_back(&if_else.instructions, instructions);
	instructions = if_else.instructions;

	fill_list(if_else.expression.true_list, if_else.true_section_line);
	fill_list(if_else.expression.false_list, if_else.false_section_line);

	fill_list(if_else.node_goto, instructions_inputed);
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

void	initialize_do(t_do *do_start)
{
	do_start->current_line = instructions_inputed;
}

void	end_do(t_do do_start, t_expression exp)
{
	fill_list(exp.true_list, instructions_inputed);
	fill_list(exp.false_list, do_start.current_line);
}

void	initialize_for_range(t_for_range *for_range, t_id id, t_expression exp1, t_expression exp2)
{
	char	*str;
	char	*iter_reg;

	// Check if type of exp1 == type of exp2
	if (exp1.type != exp2.type)
		yyparser_error("Cannot do a for each with expressions of different type!");

	if (exp1.type != INT_TYPE)
		yyparser_error("Cannot do a for each with non integer expressions!");
	
	// store to if_start all the instructions before this
	for_range->instructions = instructions;

	// reset instructions
	instructions = NULL;

	// Check if value of exp1 < value of exp2
	for_range->initial_value = *(int *)exp1.value;
	for_range->final_value = *(int *)exp2.value;

	// Initialize id
	for_range->id = id;
	id.type = INT_TYPE;
	id.value = exp1.value;
	update_id(&id);

	if (for_range->initial_value >= for_range->final_value)
		return ;

	// Create assignation to id = val1
	compile_assignation(id, exp1);

	// Create assignation $t0(regs_reserved) = last $t0x
	regs_reserved++;
	iter_reg = strjoin("$0", convert_int_to_str(regs_reserved));
	str = strjoin(iter_reg, " := ");
	str = strjoin(str, get_exp_register(exp2));
	add_instruction(str, -1);

	for_range->true_section_line = instructions_inputed;

	// Create comparation id < val2 goto nex_line
	str = strjoin("IF ", id.lexema);
	str = strjoin(str, " LTI ");
	str = strjoin(str, iter_reg);
	str = strjoin(str, " GOTO ");
	str = strjoin(str, convert_int_to_str(instructions_inputed + 2));
	add_instruction(str, -1);

	// create goto false_section_line
	for_range->end_goto = create_list(instructions_inputed);
	add_instruction(strdup("GOTO "), -1);
}

void	end_for_range(t_for_range for_range)
{
	char	*str;

	if (for_range.initial_value >= for_range.final_value)
	{
		// we erase instructions inside for range in bc it will never enter
		instructions = for_range.instructions;
		return ;
	}

	// recover instructions before if
	lstadd_back(&for_range.instructions, instructions);
	instructions = for_range.instructions;

	// Create id := id + 1
	str = strjoin(for_range.id.lexema, " := ");
	str = strjoin(str, for_range.id.lexema);
	str = strjoin(str, " ADDI 1");
	add_instruction(str, -1);

	// Create goto true_section_line
	add_instruction(strjoin("GOTO ", convert_int_to_str(for_range.true_section_line)), -1);

	// Fill false_section_line
	fill_list(for_range.end_goto, instructions_inputed);

	regs_reserved--;
}
