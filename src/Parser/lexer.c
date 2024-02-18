/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:57:42 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/18 13:49:00 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	get_pipes(t_var *var, t_list **list)
{
	t_list	*temp;

	*list = ft_lstnew(var->inputline);
	if (pipe_split(list, is_cut_point) == -1)
		return (ft_lstclear(list, free), -1);
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
	{
		ft_putstr_fd("Minishell: Syntax error: ", 2);
		ft_putstr_fd("`|` unexpected\n", 2);
		return (g_status = SYNTAX_ERROR, 2);
	}
	first_node = NULL;
	current = list;
	while (current)
	{
		var->inputline = ((char *)current->content);
		var->len_inputline = ft_strlen(var->inputline);
		var->tokens = ft_lstnew_node();
		start = 0;
		while (start < var->len_inputline)
		{
			start = gnt_startpoint(var, start);
			if (start == -1)
				return (ft_lstclear(&list, free), g_status);
		}
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
