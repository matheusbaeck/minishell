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

static	int	detect_flag(t_node *node, char *token_string)
{
	int			i;

	i = 1;
	if (ft_strncmp(token_string, "-", 1) == 0)
	{
		if (ft_strncmp(node->token->content, "echo", 4) == 0
			&& node->redir == NULL && node->where_redir == NULL)
		{
			while (token_string[i] == 'n')
				i++;
			if (token_string[i] == '\0' && node->params == NULL)
				ft_lstadd_back_subnode(&node->params, ft_lstnew_subnode(token_string));
		}
		else
			ft_lstadd_back_subnode(&node->params, ft_lstnew_subnode(token_string));
		return (0);
	}
	return (1);
}

static	int	check_flags(t_node *tokens)
{
	int			count;
	t_subnode	*subnode;
	int			flagecho;

	detect_flag(tokens, tokens->token->content); //probably not the best implementation
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

