/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:27 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/01 23:24:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	cd(t_node *tokens)
{
	char	*where;
	int		value;

	value = 0;
	if (tokens->params == NULL && tokens->params->content[0] == '-')
	{
		printf("Minishell: cd: no options can be handled.\n");
		return (EXIT_FAILURE);
	}
	if (tokens->params == NULL)
	{
		where = getenv("HOME");
		if (!where)
		{
			printf("Minishell: cd: $HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	else
		where = tokens->params->content;
	value = chdir(where);
	if (value == -1)
	{
		printf("Minishell: cd: %s: No such file or directory\n", where);
		free(where);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
