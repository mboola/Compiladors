#include "compiler.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*instructions;
FILE	*c3a_output;
int		line;
int		current_reg;
int		regs_reserved;

static void	clear_instruction(void *data)
{
	free(data);
}

static void	print_line()
{
	fprintf(c3a_output, "%d:\t", line);
	line++;
}

// 
static void print_instruction(char *instruction)
{
	print_line();
	fprintf(c3a_output, "%s", instruction);
	fprintf(c3a_output, "\n");
}

void	print_all_instructions()
{
	t_list  *lst;

	if (instructions == NULL)
		return ;
	lst = instructions;
	while (lst)
	{
		print_instruction((char *)lst->content);
		lst = lst->next;
	}

	// Here we reset the lst
	lstclear(&instructions, clear_instruction);
	instructions = NULL;
}

// Adds a new instruction into the linked list with a specified position
// If position is -1 we add it to the last position
void	add_instruction(char *instruction, int position)
{
	t_list	*node;
	t_list	*lst;
	int		i;

	node = lstnew(instruction);
	if (position == -1)
	{
		lstadd_back(&instructions, node);
		return ;
	}
	lst = instructions;
	i = 0;
	while (i < position && lst->next)
		lst = lst->next;
	lst_insert(&lst, node);
}

void	end_compilation()
{
	print_all_instructions();
	print_instruction("HALT");
}

char	open_output_file(char *file)
{
	c3a_output = fopen(file,"w");
	instructions = NULL;
	line = 1;
	current_reg = 1;
	regs_reserved = 0;
	return (c3a_output == NULL);
}

void	close_output_file()
{
	fclose(c3a_output);
}
