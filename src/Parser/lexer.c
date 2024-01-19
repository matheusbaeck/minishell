/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:57:42 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/19 00:38:29 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static int	count_lines(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);	
}


// static int	ft_lstsize_node(t_node *lst)
// {
// 	size_t	i;
// 	t_node	*ptr;

// 	i = 0;
// 	ptr = lst;
// 	while (ptr)
// 	{
// 		ptr = ptr->next;
// 		i++;
// 	}
// 	return (i);
// }

void	lexer(t_var *var)
{
	int			i;
	int			start;
	int			size;
	char		**splitted_inputline;
	t_node		*first_node;

	splitted_inputline = ft_split(var->inputline, '|');
	size = count_lines(splitted_inputline);
	i = -1;
	while (++i < size)
	{
		start = 0;
		var->inputline = splitted_inputline[i];
		var->len_inputline = ft_strlen(var->inputline);
		var->tokens = ft_lstnew_node();
		if (i == 0)
			first_node = var->tokens;
		while (start < var->len_inputline)
			start = gnt_startpoint(var, start);
		//free(splitted_inputline[i]);
		if (i != 0)
			ft_lstadd_back_node(&first_node, var->tokens);
	}
	//free(splitted_inputline);
	var->tokens = first_node;
	
}
//gnt_startpoint returns the index of the next character

