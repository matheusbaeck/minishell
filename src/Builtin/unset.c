/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:28:26 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/17 19:11:59 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static	void	deletenode_env(t_env **stack, t_env *nodeToDelete)
{
	t_env	*current;

	current = *stack;
	if (*stack == NULL || nodeToDelete == NULL)
		return ;
	if (*stack == nodeToDelete)
		*stack = nodeToDelete->next;
	else
	{
		while (current->next != NULL && current->next != nodeToDelete)
			current = current->next;
		if (current->next == NULL)
			return ;
		current->next = nodeToDelete->next;
	}
	free(nodeToDelete->line_env);
	free(nodeToDelete);
}

void	unset(t_var *var)
{
	t_subnode	*tokens;
	t_env		*tmp;

	if (var->tokens->flags != NULL)
	{
		printf("Minishell: unset: no options can be handled.\n");
		return ;
	}
	tokens = var->tokens->params;
	while (tokens)
	{
		tmp = var->envp;
		while (tmp)
		{
			if (ft_strncmp(tmp->line_env, tokens->content, \
				ft_strlen(tokens->content)) == 0)
			{
				deletenode_env(&var->envp, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		tokens = tokens->next;
	}
}
