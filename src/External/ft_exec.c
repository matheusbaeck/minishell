/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:01:41 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/26 17:44:59 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	int	is_file_or_directory(const char	*path)
{
	struct stat	filestat;

	if (stat(path, &filestat) < 0)
		return (-1);
	if (S_ISREG(filestat.st_mode))
		return (1);
	else if (S_ISDIR(filestat.st_mode))
		return (2);
	else
		return (0);
}

static	char	**find_path_env(char **envp)
{
	int		i;
	char	**tmp;
	int		len;

	len = 0;
	while (envp[len] != NULL)
		len++;
	i = 0;
	while (i < len && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (envp[i] == NULL || i >= len)
		return (NULL);
	tmp = ft_split(envp[i] + 5, ':');
	return (tmp);
}

static	int	find_path(char **envp, char	*command, char**dest)
{
	char	*temp;
	char	**path_envp;
	int		i;

	path_envp = find_path_env(envp);
	i = -1;
	while (path_envp && path_envp[++i] && command)
	{
		temp = ft_strjoin(path_envp[i], "/");
		*dest = ft_strjoin(temp, command);
		free(temp);
		if (access(*dest, F_OK) == 0)
		{
			doublefree(path_envp);
			return (0);
		}
		free(*dest);
	}
	doublefree(path_envp);
	return (1);
}

static int	if_exec_fail(char *exec_path, char ***envp, char	***args)
{
	doublefree(*envp);
	doublefree(*args);
	if (is_file_or_directory(exec_path) == 2)
		return (ft_putstr_fd("Minishell: Is a directory\n", 2), 126);
	else if (is_file_or_directory(exec_path) == 0)
	{
		if (access(exec_path, X_OK) == -1)
			return (ft_putstr_fd("Minishell: Permission denied\n", 2), 126);
		ft_putstr_fd("Minishell: command not found\n", 2);
		return (127);
	}
	else
	{
		if (is_file_or_directory(exec_path) == 1)
		{
			if (access(exec_path, X_OK) == -1)
				return (ft_putstr_fd("Minishell: Permission denied\n", 2), 126);
		}
	}
	ft_putstr_fd("Minishell: No such file or directory\n", 2);
	return (127);
}

int	ft_exec(t_var	*var)
{
	char	**args;
	char	**envp;
	char	*exec_path;
	int		exit_value;

	if (!var->tokens || !var->tokens->token)
		exit(0);
	args = set_params_to_array(var->tokens);
	envp = envlist_to_array(var->envp);
	if (!(ft_strncmp(var->tokens->token->content, "./", 2)
			&& ft_strncmp(var->tokens->token->content, "/", 1)
			&& ft_strncmp(var->tokens->token->content, "../", 3)))
		exec_path = var->tokens->token->content;
	else if (envp && find_path(envp, var->tokens->token->content, &exec_path))
		exit(ms_error(var->tokens->token->content, "command not found", 127));
	if (execve(exec_path, args, envp) == -1)
	{
		exit_value = if_exec_fail(exec_path, &envp, &args);
		free(exec_path);
		exit (exit_value);
	}
	exit (EXIT_FAILURE);
}
