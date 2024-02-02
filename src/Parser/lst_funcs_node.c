/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:19:53 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/02 00:20:13 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	ft_freenode(t_node **node)
{
	t_node	*current;

	current = *node;
	if (current->token != NULL)
		ft_lstclear_subnode(&current->token);
	if (current->params != NULL)
		ft_lstclear_subnode(&current->params);
	if (current->redir != NULL)
		ft_lstclear_subnode(&current->redir);
	if (current->where_redir != NULL)
		ft_lstclear_subnode(&current->where_redir);
	free(current);
}

void	ft_lstdelone_node(t_node *node)
{
	if (node->token != NULL)
		ft_lstclear_subnode(&node->token);
	if (node->params != NULL)
		ft_lstclear_subnode(&node->params);
	if (node->redir != NULL)
		ft_lstclear_subnode(&node->redir);
	if (node->where_redir != NULL)
		ft_lstclear_subnode(&node->where_redir);
	free(node);
}

t_node	*ft_lstdelone_node_getnext(t_node *node)
{
	t_node	*current;

	if (!node)
		return (NULL);
	current = node;
	node = node->next;
	ft_lstdelone_node(current);
	return (node);
}

void	ft_lstclear_node(t_node **lst)
{
	t_node	*current;


	if (!lst || !*lst)
		return ;

	while (*lst)
	{
		current = *lst;
		*lst = (*lst)->next;
		if (current->token != NULL)
			ft_lstclear_subnode(&current->token);
		if (current->params != NULL)
			ft_lstclear_subnode(&current->params);
		if (current->redir != NULL)
			ft_lstclear_subnode(&current->redir);
		if (current->where_redir != NULL)
			ft_lstclear_subnode(&current->where_redir);
		free(current);
	}
}

t_node	*ft_lstnew_node(void)
{
	t_node	*ptr;

	ptr = (t_node *)malloc(sizeof(t_node));
	if (!(ptr))
		return (NULL);
	ptr->token = NULL;
	ptr->params = NULL;
	ptr->redir = NULL;
	ptr->where_redir = NULL;
	ptr->next = NULL;
	return (ptr);
}

t_node	*ft_lstlast_node(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_node(t_node **lst, t_node *new)
{
	t_node	*ptr;

	ptr = ft_lstlast_node(*lst);
	if (ptr != NULL)
		ptr->next = new;
	else
		*lst = new;
}
