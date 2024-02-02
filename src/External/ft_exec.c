/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:01:41 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/02 17:34:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	char	**malloc_params_node(t_node *node)
{
	t_subnode	*tmp;
	int			size;
	char		**args;

	size = 1;
	tmp = (*node).params;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	printf("malloc size: %i", size);
	args = (char **)malloc((size + 1) * sizeof(char *));
	if (!args)
		return(NULL);
	return (args);
}

static	char	**set_params_to_array(t_node *node)
{
	t_subnode	*tmp;
	char		**args;
	int			i;

	args = malloc_flagsandparams_node(node);
	if (!args)
		return (NULL);
	i = 0;
	if (node->token->content != NULL)
		args[i++] = ft_strdup(node->token->content);
	tmp = (*node).params;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

char	**envlist_to_array(t_env *envlist)
{
	char	**envp;
	t_env	*tmp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	tmp = envlist;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	envp = (char **)malloc((count + 1) * sizeof(char *));
	tmp = envlist;
	while (i < count)
	{
		envp[i++] = ft_strdup(tmp->line_env);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

static	char	**find_path_env(char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
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
	while (path_envp[++i] && command)
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

int		ft_exec(t_var *var)
{
	char	**args;
	char	**envp;
	char	*exec_path; //can change for var.inputline to norminette
	
	args = set_params_to_array(var->tokens);
	envp = envlist_to_array(var->envp);
	if (!(ft_strncmp(var->tokens->token->content, "./", 2) 
		&& ft_strncmp(var->tokens->token->content, "/", 1) 
		&& ft_strncmp(var->tokens->token->content, "../", 3)))
		exec_path = var->tokens->token->content;
	else if (find_path(envp, var->tokens->token->content, &exec_path))
		exec_path = var->tokens->token->content;
	if (execve(exec_path, args, envp) == -1)
	{
		doublefree(envp);
		doublefree(args);
		if (!access(exec_path, F_OK) && access(exec_path, X_OK))
		{
			perror("access");
			exit (PERMISSION_DENIED);
		}
		perror("execve");
		free(exec_path);
		exit(127);
	}
	return(EXIT_FAILURE);
}
