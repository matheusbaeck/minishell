/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:36:16 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/25 02:15:33 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	env(t_var *var)
{
	t_env	*tmp;

	if (no_flags_supported(var->tokens->params))
		return (1);
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
