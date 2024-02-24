/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:57:42 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/24 18:53:10 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	is_pipe(int c)
{
	if (c == '|')
		return (1);
	return (0);
}

static int	is_quote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

// On success return index of closing char, if not find return '\0'
static int	jumpe_content(const char	*line, char open, char close)
{
	int	nesting_level;
	int	i;

	i = 0;
	nesting_level = 1;
	while (line[++i])
	{
		if (close != open && line[i] == open)
			nesting_level++;
		else if (line[i] == close)
		{
			nesting_level--;
			if (nesting_level == 0)
				return (i);
		}
	}
	return (i);
}

// On success return index of pipe, if not find return '\0'
static int	pipechr(char *str)
{
	int	i;
	int	j;

	i = -1;
	//printf("on pipechr:%s\n", str);
	while (str[++i])
	{
		//printf("char:%c:", str[i]);
		if (is_quote(str[i]))
		{
			j = i + jumpe_content(&str[i], str[i], str[i]);
			//printf("quote %d to %d\n", i , j);
			if (str[j] == '\0')
				return (j);
			i = j;
		}
		else if (is_pipe(str[i]))
		{
			//printf("pipe\n");
			return (i);
		}
		//printf("none\n");
	}
	return (i);
}

static int	get_pipes(t_var *var, t_list **list)
{
	char	*new_content;
	int		i;
	int		j;

	//printf("inicio: input:%s\n", var->inputline);
	i = 0;
	*list = NULL;
	while (var->inputline[i])
	{
		j = pipechr(&var->inputline[i]);
		//printf("j:%d\n", j);
		new_content = (char *)ft_calloc(j - i + 1, sizeof(char));
		ft_strlcpy(new_content, &var->inputline[i], j - i + 1);
		//printf("new_content:%s %d\n", new_content, ft_strlen(new_content));
		ft_lstadd_back(list, ft_lstnew(new_content));
		//printf("listlast:%s\n", (char *)ft_lstlast(*list)->content);
		i += j;
	}
	free(var->inputline);
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
	ft_lstclear(&list, free);
	return (0);
}
