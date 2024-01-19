/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:07:23 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/17 19:07:15 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static	int	check_flags(t_node *tokens)
{
	int			count;
	t_subnode	*subnode;

	count = 0;
	subnode = tokens->flags;
	if (!tokens || !subnode)
		return (0);
	if (subnode->content[count] == '-')
	{
		count++;
		while (subnode->content[count] == 'n')
			count++;
		if (subnode->content[count] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	echo(t_node *tokens)
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
		if (i > 0)
			printf(" ");
		if (str->content)
			printf("%s", str->content);
		str = str->next;
		i++;
	}
	if (flagecho == 0)
		printf("\n");
}

