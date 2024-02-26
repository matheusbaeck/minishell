/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:57:42 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/26 17:30:18 by math             ###   ########.fr       */
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

static	int	tokenize_cmd(t_var *var, int *start, t_list	*list)
{
	*start = 0;
	while (*start < var->len_inputline)
	{
		*start = gnt_startpoint(var, *start);
		if (*start == -1)
			return (ft_lstclear(&list, free), g_status);
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
		return (ft_putstr_fd("Minishell: Syntax error\n", 2), 2);
	first_node = NULL;
	current = list;
	while (current)
	{
		var->nb_node++;
		var->inputline = ((char *)current->content);
		var->len_inputline = ft_strlen(var->inputline);
		var->tokens = ft_lstnew_node();
		if (tokenize_cmd(var, &start, current))
			return (g_status);
		if (list == current)
			first_node = var->tokens;
		else
			ft_lstadd_back_node(&first_node, var->tokens);
		current = current->next;
	}
	var->tokens = first_node;
	return (ft_lstclear(&list, free), 0);
}
