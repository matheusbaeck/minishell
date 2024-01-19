/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:02:57 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/17 18:46:10 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

t_env	*new_node_env(const char *line_env, int exported)
{
	t_env	*node_tmp;

	node_tmp = (t_env *)malloc(sizeof(t_env));
	if (!(node_tmp))
		return (NULL);
	node_tmp->line_env = ft_strdup(line_env);
	node_tmp->exported = exported;
	node_tmp->next = NULL;
	return (node_tmp);
}

static	t_env	*ft_lastnode_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_addback_node_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	ptr = ft_lastnode_env(*lst);
	if (ptr != NULL)
		ptr->next = new;
	else
		*lst = new;
}

void	ft_freeenv(t_env **lst)
{
	t_env	*current;

	if (!lst || !(*lst))
		return ;

	while (*lst)
	{
		current = *lst;
		*lst = (*lst)->next;
		free(current->line_env);
		free(current);
	}
}

void	cpy_env(t_env **ptr, const char **envp)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	while (i < len)
		ft_addback_node_env(ptr, new_node_env(envp[i++], 0));
}