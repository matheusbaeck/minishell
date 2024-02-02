/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:07:23 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/02 15:14:06 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

// static	int	detect_flag(t_node *node, char *token_string)
// {
// 	int			i;

// 	i = 1;
// 	if (ft_strncmp(token_string, "-", 1) == 0)
// 	{
// 		if (ft_strncmp(node->token->content, "echo", 4) == 0
// 			&& node->redir == NULL && node->where_redir == NULL)
// 		{
// 			while (token_string[i] == 'n')
// 				i++;
// 			if (token_string[i] == '\0' && node->params == NULL)
// 				ft_lstadd_back_subnode(&node->params, ft_lstnew_subnode(token_string));
// 		}
// 		else
// 			ft_lstadd_back_subnode(&node->params, ft_lstnew_subnode(token_string));
// 		return (0);
// 	}
// 	return (1);
// }

// static	int	check_flags(t_node *tokens)
// {
// 	int			count;
// 	t_subnode	*subnode;
// 	int			flagecho;

// 	detect_flag(tokens, tokens->token->content); //probably not the best implementation
// 	flagecho = 0;
// 	count = 0;
// 	subnode = tokens->flags;
// 	if (!tokens || !subnode)
// 		return (0);
// 	while (subnode)
// 	{
// 		if (subnode->content && subnode->content[count] == '-')
// 		{
// 			count++;
// 			while (subnode->content[count] == 'n')
// 				count++;
// 			if (subnode->content[count] == '\0')
// 				flagecho = 1;
// 		}
// 		subnode = subnode->next;
// 	}
// 	return (flagecho);
// }

static int	is_flag(char *str)
{
	if (ft_strncmp("-n", str, ft_strlen(str)))
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

