/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nodeprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:25:20 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/08 00:25:20 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void printNode(t_node *node)
{
	if (node == NULL)
	{
		printf("NULL\n");
		return;
	}
	printf("Token: %s\n", node->token->content);

	// Print params
	printf("Params: ");
	t_subnode *params = node->params;
	while (params != NULL)
	{
		printf("%s ", params->content);
		params = params->next;
	}
	printf("\n");

	// Print redir
	printf("Redir: ");
	t_subnode *redir = node->redir;
	while (redir != NULL)
	{
		printf("%s ", redir->content);
		redir = redir->next;
	}
	printf("\n");

	// Print where_redir
	printf("Where Redir: ");
	t_subnode *where_redir = node->where_redir;
	while (where_redir != NULL)
	{
		printf("%s ", where_redir->content);
		where_redir = where_redir->next;
	}
	printf("\n");

}

void    printNodes(t_node **node)
{
	int     i;
	t_node  *tmp;

	tmp = *node;
	i = 0;
	while (tmp)
	{
		++i;
		printf("NODE -> %i\n", i);
		printNode(tmp);
		tmp = tmp->next;
	}
	printf("EXECUTION:\n");
}
