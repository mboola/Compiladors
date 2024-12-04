#include "linked_list.h"
#include "yyfunctions.h"
#include <stdlib.h>

t_list	*lstnew(void *content)
{
    t_list	*node;

	node = yymalloc(sizeof(t_list));
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*lstlast(t_list *lst)
{
    if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int		lstsize(t_list *lst)
{
    int	len;

	if (lst == NULL)
		return (0);
	len = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	lstadd_back(t_list **lst, t_list *node)
{
    if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
		lstlast(*lst)->next = node;
}

void	lst_insert(t_list **lst, t_list *node)
{
    t_list  *next;

    if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
        next = (*lst)->next;
        (*lst)->next = node;
		node->next = next;
	}
}

void	lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	tmp = *lst;
	while (tmp->next != NULL)
	{
		*lst = (*lst)->next;
		lstdelone(tmp, del);
		tmp = *lst;
	}
	lstdelone(tmp, del);
	*lst = NULL;
}

void	lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
