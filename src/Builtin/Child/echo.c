/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:07:23 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/25 02:24:44 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

static	int	check_flags(t_node *tokens)
{
	int			count;
	t_subnode	*subnode;
	int			flagecho;

	flagecho = 0;
	count = 0;
	subnode = tokens->flags;
	if (!tokens || !subnode)
		return (0);
	while (subnode)
	{
		if (subnode->content && subnode->content[count] == '-')
		{
			count++;
			while (subnode->content[count] == 'n')
				count++;
			if (subnode->content[count] == '\0')
				flagecho = 1;
		}
		subnode = subnode->next;
	}
	return (flagecho);
}

int	echo(t_node *tokens)
{
	int			flagecho;
	t_subnode	*str;
	int			i;

	i = 0;
	flagecho = 0;
	str = tokens->params;
	flagecho = check_flags(tokens);
	while (str)
	{
		if (str->content)
		{
			ft_printf(" ");
			ft_printf("%s", str->content);
		}
		str = str->next;
		i++;
	}
	if (flagecho == 0)
		ft_printf("\n");
	return (0);
}

