/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:07:23 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/08 17:11:27 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"


static int	is_flag(char *str)
{
	if (ft_strncmp("-n", str, 2))
		return (0);
	return (1);
}

int	echo(t_node *tokens)
{
	int			flag;
	t_subnode	*subnode;

	flag = 0;
	while (tokens->params && is_flag(tokens->params->content))
	{
		flag = 1;
		subnode = tokens->params;
		tokens->params = tokens->params->next;
		ft_lstdelone_subnode(subnode);
	}
	while (tokens->params)
	{
		printf("%s", tokens->params->content);
		if(tokens->params->next)
			printf(" ");
		subnode = tokens->params;
		tokens->params = tokens->params->next;
		ft_lstdelone_subnode(subnode);
	}
	if (flag == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}


