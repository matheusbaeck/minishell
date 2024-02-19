/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nodeprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:25:20 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/19 15:49:32 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	printnode_norm(t_node	*node)
{
	t_subnode	*redir;
	t_subnode	*where_redir;

	printf("Redir: ");
	redir = node->redir;
	while (redir != NULL)
	{
		printf("%s ", redir->content);
		redir = redir->next;
	}
	printf("\n");
	printf("Where Redir: ");
	where_redir = node->where_redir;
	while (where_redir != NULL)
	{
		printf("%s ", where_redir->content);
		where_redir = where_redir->next;
	}
	printf("\n");
}

static	void	printnode(t_node	*node)
{
	t_subnode	*params;

	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	if (node->token)
		printf("Token: %s\n", node->token->content);
	printf("Params: ");
	params = node->params;
	while (params != NULL)
	{
		printf("%s ", params->content);
		params = params->next;
	}
	printf("\n");
	printnode_norm(node);
}

void	printnodes(t_node	**node)
{
	int		i;
	t_node	*tmp;

	tmp = *node;
	i = 0;
	while (tmp)
	{
		++i;
		printf("NODE -> %i\n", i);
		printnode(tmp);
		tmp = tmp->next;
	}
	printf("EXECUTION:\n");
}
