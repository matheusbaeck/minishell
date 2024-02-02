/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:07:23 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/01 19:44:29 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../header.h"

static	int	check_flags(t_node *tokens)
{
	t_subnode	*subnode;
	int			flagecho;

	flagecho = 0;
	subnode = tokens->params;
	if (!tokens || !subnode)
		return (0);
	if (subnode)
	{
		if (subnode->content && subnode->content[0] == '-')
		{
			if (subnode->content[1] == 'n'
				&& ((subnode->content[2] == '\0') 
				|| (ft_isspace(subnode->content[2]) || subnode->content[2] == '\n')))
				flagecho = 1;
		}
	}
	return (flagecho);
}

int	echo(t_node *tokens)
{
	int			flagecho;
	t_subnode	*str;

	flagecho = 0;
	str = tokens->params;
	flagecho = check_flags(tokens);
	if (flagecho)
		str = str->next;
	while (str)
	{
		if (str->content)
		{
			ft_printf(" ");
			ft_printf("%s", str->content);
		}
		str = str->next;
	}
	if (flagecho == 0)
		ft_printf("\n");
	return (0);
}


