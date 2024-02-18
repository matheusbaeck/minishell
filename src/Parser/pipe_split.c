/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:52:09 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/18 14:05:34 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	is_operator_or(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return (2);
	return (0);
}

static int	is_operator_and(char *line)
{
	if (line[0] == '&' && line[1] == '&')
		return (2);
	return (0);
}

static int	is_operator_pipe(char *line)
{
	if (line[0] == '|' && !is_operator_or(line))
		return (1);
	return (0);
}

static int	is_operator_bkgexec(char *line)
{
	if (line[0] == '&' && !is_operator_and(line))
		return (1);
	return (0);
}

static int	is_operator_semicolon(char *line)
{
	if (line[0] == ';')
		return (1);
	return (line[0] == ';');
}

static int	is_operator_grouping(char *line)
{
	if (line[0] == '(' || line[0] == ')' || line[0] == '{' || line[0] == '}')
		return (1);
	return (0);
}

int	is_cut_point(char *line)
{
	if (is_operator_and(line) || is_operator_or(line)
		|| is_operator_bkgexec(line) || is_operator_semicolon(line)
		|| is_operator_semicolon(line) || is_operator_grouping(line))
		return (-1);
	return (is_operator_pipe(line));
}

static char	*str_cut(char **s1, int start, int skip)
{
	char	*s2;
	char	*temp;

	if (start < 0 || start + skip >= ft_strlen(*s1))
		return (NULL);
	s2 = malloc((ft_strlen(&(*s1)[start + skip]) + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &(*s1)[start + skip], ft_strlen(&(*s1)[start + skip]) + 1);
	temp = *s1;
	*s1 = malloc((start + 1) * sizeof(char));
	if (!(*s1))
		return (NULL);
	ft_strlcpy(*s1, temp, start + 1);
	free(temp);
	return (s2);
}

static int	jumper(const char	*line, char open, char close)
{
	int	nesting_level;
	int	i;

	i = 0;
	if (line[i] != open)
		return (i);
	nesting_level = 1;
	while (line[++i] || nesting_level > 0)
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

int	pipe_split(t_list **node, int (*fptr)(char *))
{
	t_list	*current;
	int		i;
	int		ret;

	current = *node;
	while (current)
	{
		i = -1;
		while (((char *)current->content)[++i])
		{
			i += jumper(&(((char *)current->content)[i]), '\'', '\'');
			if (!((char *)current->content)[i])
				return (0);
			i += jumper(&(((char *)current->content)[i]), '\"', '\"');
			if (!((char *)current->content)[i])
				return (0);
			ret = fptr(&(((char *)current->content)[i]));
			if (ret > 0)
			{
				ft_lstadd_back(node, ft_lstnew((void *)str_cut((char **)(&current->content), i, 1)));
				if (current->next->content == NULL)
					return (free(current->next), current->next = NULL, -1);
				break ;
			}
			else if (ret < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
