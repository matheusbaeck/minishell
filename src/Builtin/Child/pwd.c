/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 03:41:02 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/29 15:24:47 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	no_flags_supported(t_subnode *subnode_param)
{
	t_subnode	*subnode;
	int			flagecho;

	flagecho = 0;
	subnode = subnode_param;
	if (!subnode)
		return (0);
	while (subnode)
	{
		if (subnode->content && subnode->content[0] == '-')
		{
			ft_putstr_fd("Minishell: Illegal option ", 2);
			ft_putstr_fd(subnode->content, 2);
			ft_putstr_fd("\n", 2);
			return (SYNTAX_ERROR);
		}
		subnode = subnode->next;
	}
	return (flagecho);
}

int	pwd(t_var	*var)
{
	char	*path;

	if (no_flags_supported(var->tokens->params))
		return (SYNTAX_ERROR);
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}
