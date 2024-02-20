/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:52:09 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 17:13:32 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

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

static	int	jump_content(int *i, t_list	*cur, int *ret, int (*fptr)(char *))
{
	*i += jumper(&(((char *)cur->content)[*i]), '\'', '\'');
	if (!((char *)cur->content)[*i])
		return (-1);
	*i += jumper(&(((char *)cur->content)[*i]), '\"', '\"');
	if (!((char *)cur->content)[*i])
		return (-1);
	*ret = fptr(&(((char *)cur->content)[*i]));
	return (*ret);
}

int	pipe_split(t_list **node, int (*fptr)(char *))
{
	t_list	*cur;
	int		i;
	int		ret;

	cur = *node;
	while (cur)
	{
		i = -1;
		while (((char *)cur->content)[++i])
		{
			jump_content(&i, cur, &ret, fptr);
			if (ret > 0)
			{
				ft_lstadd_back(node,
					ft_lstnew((void *)str_cut((char **)(&cur->content), i, 1)));
				if (cur->next->content == NULL)
					return (free(cur->next), cur->next = NULL, -1);
				break ;
			}
			else if (ret < 0)
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}
