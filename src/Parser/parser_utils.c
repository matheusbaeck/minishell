/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:29:52 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 16:35:17 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

t_node	*ft_lstdelone_node_getnext(t_node *node)
{
	t_node	*current;

	if (!node)
		return (NULL);
	current = node;
	node = node->next;
	ft_lstdelone_node(current);
	return (node);
}

int	is_operator_semicolon(char *line)
{
	if (line[0] == ';')
		return (1);
	return (line[0] == ';');
}

int	is_operator_grouping(char *line)
{
	if (line[0] == '(' || line[0] == ')' || line[0] == '{' || line[0] == '}')
		return (1);
	return (0);
}
