/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:27 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/17 19:06:35 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	cd(t_node *tokens)
{
	char	*where;
	int		value;

	value = 0;
	if (tokens->flags != NULL)
	{
		printf("Minishell: cd: no options can be handled.\n");
		return (1);
	}
	if (tokens->params == NULL)
	{
		where = getenv("HOME");
		if (!where)
			return (printf("Minishell: cd: $HOME not set\n"));
	}
	else
		where = tokens->params->content;
	value = chdir(where);
	if (value == -1)
	{
		printf("Minishell: cd: %s: No such file or directory\n", where);
		free(where);
		return (-1);
	}
	return (0);
}
