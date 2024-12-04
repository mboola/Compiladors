#ifndef LINKED_LIST_H
# define LINKED_LIST_H

// Definition of a linked list and its functions

typedef struct t_list
{
	void			*content;
	struct t_list	*next;
}	t_list;

/*
 *	Functions that define, modify or delete a one way linked list.
 */
t_list	*lstnew(void *content);
t_list	*lstlast(t_list *lst);
int		lstsize(t_list *lst);
void	lstadd_back(t_list **lst, t_list *node);
void	lst_insert(t_list **lst, t_list *node);
void	lstclear(t_list **lst, void (*del)(void *));
void	lstdelone(t_list *lst, void (*del)(void *));

#endif
