/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:33:24 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 18:08:08 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	add_mode_op(t_var *var, int *start, int *i, char *token_string)
{
	if (var->tokens == NULL)
		ft_lstadd_back_node(&var->tokens, ft_lstnew_node());
	token_string = ft_substr(var->inputline, *start, (*i) - (*start));
	*start = *i;
	if (*token_string)
		ft_lstadd_back_subnode(&var->tokens->redir,
			ft_lstnew_subnode(token_string));
}

static	int	add_cmd_or_whredir_or_param(t_var *var, char	**str, int *whredir)
{
	if ((*str) != NULL
		&& *(*str) != '\0' && *(*str) != '|' && var->tokens)
	{
		if (*whredir)
		{
			return (ft_lstadd_back_subnode(&var->tokens->where_redir,
					ft_lstnew_subnode((*str))), 0);
		}
		else if (var->tokens->token == NULL)
			return (ft_lstadd_back_subnode(&var->tokens->token,
					ft_lstnew_subnode((*str))), 0);
		else
			return (ft_lstadd_back_subnode(&var->tokens->params,
					ft_lstnew_subnode((*str))), 0);
	}
	if (*whredir && ((*str) == NULL || *(*str) == '\0'))
	{
		ft_putstr_fd("Minishell: Syntax error\n", 2);
		g_status = SYNTAX_ERROR;
		return (0);
	}
	return (1);
}

static	int	check_input_and_skip_spaces(t_var *var, int *start, int *i)
{
	if ((var->inputline == NULL) && *start < var->len_inputline)
		return (1);
	while (var->inputline[*start] == ' ' || var->inputline[*start] == '\t')
		(*start)++;
	*i = *start;
	return (0);
}

static	int	add_redir_op(t_var *var, int *start, int *i, char *str)
{
	if (isdouble_operator(var->inputline, *i))
	{
		if (str != NULL)
			return (-1);
		*i = (*i) + 2;
		add_mode_op(var, start, i, str);
		return (1);
	}
	else if (isingle_operator(var->inputline, *i))
	{
		if (str != NULL)
			return (-1);
		(*i)++;
		add_mode_op(var, start, i, str);
		return (1);
	}
	return (0);
}

int	gnt_startpoint(t_var *var, int start)
{
	char		*token_string;
	int			i;
	int			wh_redir_flg;

	i = start;
	wh_redir_flg = 0;
	token_string = NULL;
	check_input_and_skip_spaces(var, &start, &i);
	while (i < var->len_inputline
		&& (!is_space_or_eof(var->inputline[i]) || wh_redir_flg == 1))
	{
		wh_redir_flg = add_redir_op(var, &start, &i, token_string);
		if (wh_redir_flg == -1)
			break ;
		else
		{
			check_input_and_skip_spaces(var, &start, &i);
			token_string = check_word_rec(var, &start, &i, token_string);
			//printf("token: %s\n", token_string);
			if (wh_redir_flg == 1 && is_space_or_eof(var->inputline[i]))
				break ;
		}
	}
	add_cmd_or_whredir_or_param(var, &token_string, &wh_redir_flg);
	return (i);
}
