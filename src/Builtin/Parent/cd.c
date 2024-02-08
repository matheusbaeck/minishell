/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:27 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/08 17:00:28 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

static int	cd_safe(char *where)
{
	int		wstatus;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		errno = 0;
		if (chdir(where) == -1)
		{
			if (where[0] == '-')
			{
				ft_putstr_fd("Minishell: cd: no options can be handled.\n", 2);
				exit (1);
			}
			perror("chdir");
		}
		exit (0);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return(WEXITSTATUS(wstatus));
	else
		printf("unkwonw error!\n");
	return (-1);
}

int	cd(t_node *tokens)
{
	char	*where;
	int		status;

	if (tokens->params && tokens->params->next)
		return (printf("Minishell: cd: too many arguments\n"), 1);
	if (tokens->params == NULL)
	{
		where = getenv("HOME");
		if (!where)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		where = tokens->params->content;
	printf("status:%i", status);
	if (status == 0 && !tokens->next)
	{
		chdir(where);
		return (EXIT_SUCCESS);
	}
	return (status);
}
