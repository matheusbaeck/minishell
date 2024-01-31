/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:57:42 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/31 13:55:36 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	get_pipes(t_var *var, t_list **list)
{
	t_list	*temp;

	*list = ft_lstnew(var->inputline);
	if (pipe_split(list, is_cut_point) == -1)
		return (ft_lstclear(list, free), free(var->inputline), -1);
	temp = *list;
	while (temp)
	{
		temp = temp->next;
	}
	return (0);
}

int	lexer(t_var *var)
{
	int			start;
	t_node		*first_node;
	t_list		*list;
	t_list		*current;

	if (get_pipes(var, &list) == -1)
		return(var->exit_status = SYNTAX_ERROR, -1);
	first_node = NULL;
	current = list;
	while (current)
	{
		var->inputline = ((char *)current->content);
		var->len_inputline = ft_strlen(var->inputline);
		var->tokens = ft_lstnew_node();
		start = 0;
		while (start < var->len_inputline)
			start = gnt_startpoint(var, start);
		if (list == current)
			first_node = var->tokens;
		else
			ft_lstadd_back_node(&first_node, var->tokens);
		current = current->next;
	}
	var->tokens = first_node;
	ft_lstclear(&list, free);
	return (0);
}
//gnt_startpoint returns the index of the next character

