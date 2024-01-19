/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:36:16 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/17 19:07:24 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	env(t_var *var)
{
	t_env	*tmp;

	if (var->tokens->flags != NULL)
	{
		printf("Minishell: env: no options can be handled.\n");
		return (1);
	}
	tmp = var->envp;
	while (tmp)
	{
		if (tmp->exported == 0)
		{
			ft_putendl_fd(tmp->line_env, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
