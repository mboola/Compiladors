#include "compiler.h"
#include "yyfunctions.h"
#include "str_functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_list	*instructions;
FILE	*c3a_output;
int		line;	// written in file
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

static void	modify_instruction(int pos, char *modification)
{
	int i;
	char	*instruction;
	t_list	*lst;

	lst = instructions;
	i = line; //last position
	while (i < pos && lst->next)
		lst = lst->next;
	instruction = (char *)(lst->content);
	instruction = strjoin(instruction, modification);
	lst->content = instruction;
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
	c3a_output = fopen(file, "w");
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

t_list	*create_list(int position)
{
	int		*content;

	content = yymalloc(sizeof(int));
	*content = position;
	return (lstnew(content));
}

t_list	*join_list(t_list **first, t_list *second)
{
	lstadd_back(first, second);
	return *first;
}

static char	*convert_int_to_str(int i)
{
	char num[12]; //MAX NEGATIVE INT 11 chars + '\0'

	sprintf(num, "%d", i);
	return (strdup(num));
}

void	fill_list(t_list *lst, int goto_position)
{
	int	position;

	while (lst->next)
	{
		position = *(int *)(lst->content);
		modify_instruction(position, convert_int_to_str(goto_position));
		lst = lst->next;
	}
}
