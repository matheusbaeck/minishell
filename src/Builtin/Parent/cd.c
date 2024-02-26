/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:27 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/26 17:40:32 by math             ###   ########.fr       */
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
				exit(ms_error("cd", "-l: invalid option", 1));
			perror("Minishell: cd");
			exit(1);
		}
		exit (0);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (-1);
}

int	cd(t_node *tokens, int nb_node)
{
	char	*where;
	int		status;

	if (tokens->params == NULL)
	{
		where = getenv("HOME");
		if (!where)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (tokens->params->next)
		return (ft_putstr_fd("Minishell: cd: too many arguments\n", 2), 1);
	else if (tokens->next || nb_node > 1)
		return (EXIT_SUCCESS);
	else
		where = tokens->params->content;
	status = cd_safe(where);
	if (status == 0 && !tokens->next)
	{
		chdir(where);
		return (EXIT_SUCCESS);
	}
	return (status);
}
