/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:38:50 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/18 13:38:50 by smagniny         ###   ########.fr       */
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
	args = (char **)malloc((size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

char	**set_params_to_array(t_node *node)
{
	t_subnode	*tmp;
	char		**args;
	int			i;

	args = malloc_params_node(node);
	if (!args)
		return (NULL);
	i = 0;
	if (node->token && node->token->content != NULL)
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
	envp = NULL;
	tmp = envlist;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	if (count > 0)
	{
		envp = (char **)malloc((count + 1) * sizeof(char *));
		if (!envp)
			return (NULL);
	}
	tmp = envlist;
	while (i < count)
	{
		envp[i++] = ft_strdup(tmp->line_env);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
