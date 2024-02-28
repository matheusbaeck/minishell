/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:35:50 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/28 13:20:59 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	cpy_lim(char **str, char *c, int *flag, int *j)
{
	(*str)[(*j)] = *c;
	(*j)++;
	*flag = 1;
}

static	int	check_lim(int j, char *lim, char *str, char buffer)
{
	if (j == ft_strlen(lim)
		&& ft_strncmp(str, lim, ft_strlen(lim)) == 0
		&& buffer == 10)
		return (1);
	else
		return (0);
}

static	void	cpy_content(int *fd, char *str, char *lim, int *flag)
{
	write(*fd, str, ft_strlen(str));
	ft_bzero(str, ft_strlen(lim) - 1);
	*flag = 0;
}

static	void	initialize_values(int *flag, char *buffer, int *err, int *j)
{
	write(1, ">", 1);
	*flag = 0;
	*buffer = 0;
	*err = 1;
	*j = 0;
}

int	here_doc_loop(int fd, char *str, char *lim)
{
	int		j;
	char	buffer;
	int		err;
	int		flag;

	while (42)
	{
		initialize_values(&flag, &buffer, &err, &j);
		while (err && buffer != 10)
		{
			if (get_char_hd(&err, &buffer, lim) == 0)
				return (0);
			if (j < ft_strlen(lim) && lim[j] == buffer)
				cpy_lim(&str, &buffer, &flag, &j);
			else
			{
				if (flag && check_lim(j, lim, str, buffer) == 1)
					return (0);
				else if (flag)
					cpy_content(&fd, str, lim, &flag);
				write(fd, &buffer, 1);
			}
		}
	}
	return (0);
}
