/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:33:24 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/01 19:40:11 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	add_operator(t_var *var, int *start, int *i,
	char **prev_token_string, int flag_len_operator)
{
	if (var->tokens == NULL)
		ft_lstadd_back_node(&var->tokens, ft_lstnew_node());
	(*i) += flag_len_operator;
	(*prev_token_string) = ft_substr(var->inputline, *start, (*i) - (*start));
	*start = *i;
	ft_lstadd_back_subnode(&var->tokens->redir, ft_lstnew_subnode(*prev_token_string)); //libero prev_token_string dentro de lstnew_subnode.
	while (ft_isspace(var->inputline[*start])) // el token despues de un operador es el nombre del archivo al cual hay que redirigir (aplicar el operador).
		(*start)++;
	(*i) = (*start);
	*prev_token_string = 0;
	*prev_token_string = check_word_rec(var, start, i, NULL);
	ft_lstadd_back_subnode(&var->tokens->where_redir, ft_lstnew_subnode(*prev_token_string)); // añadimos el token al subnodo a where_redir
	// checkear disponibilidad archivo en caso de input
	*prev_token_string = NULL;
}

// static	int	detect_flag(t_var *var, char *token_string)
// {
// 	int			i;

// 	i = 1;
// 	if (ft_strncmp(token_string, "-", 1) == 0)
// 	{
// 		if (ft_strncmp(var->tokens->token->content, "echo", 4) == 0
// 			&& var->tokens->redir == NULL && var->tokens->where_redir == NULL)
// 		{
// 			while (token_string[i] == 'n')
// 				i++;
// 			if (token_string[i] == '\0' && var->tokens->params == NULL)
// 				ft_lstadd_back_subnode(&var->tokens->params, ft_lstnew_subnode(token_string));
// 		}
// 		else
// 			ft_lstadd_back_subnode(&var->tokens->params, ft_lstnew_subnode(token_string));
// 		return (0);
// 	}
// 	return (1);
// }

static	void	add_cmd_or_flag_or_param(t_var *var, char	**prev_token_string)
{
	if ((*prev_token_string) != NULL
		&& *(*prev_token_string) != '\0' && *(*prev_token_string) != '|' && var->tokens)
	{
		if (var->tokens->token == NULL)
			ft_lstadd_back_subnode(&var->tokens->token, ft_lstnew_subnode((*prev_token_string)));
		else
			ft_lstadd_back_subnode(&var->tokens->params, ft_lstnew_subnode((*prev_token_string)));
	}
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

int	gnt_startpoint(t_var *var, int start)
{
	char		*token_string;
	int			i;

	i = 0;
	token_string = NULL;
	if (check_input_and_skip_spaces(var, &start, &i))
		return (0); // or 1 ? if *start < var->len_inputline
	while (i < var->len_inputline && !is_space_or_eof(var->inputline[i]))//until a space or EOF
	{
		if (isdouble_operator(var->inputline, i))// tokenize >> <<
		{
			if (token_string != NULL) // un operador marca el fin del token antieror (si hay). (ex: ls>test) '>' marca el fin del token 'ls'
				break ;
			add_operator(var, &start, &i, &token_string, 2);
		}
		else if (isingle_operator(var->inputline, i)) // tokenize > < 
		{
			if (token_string != NULL)
				break ;
			add_operator(var, &start, &i, &token_string, 1);
		}
		else
			token_string = check_word_rec(var, &start, &i, token_string);
	}
	add_cmd_or_flag_or_param(var, &token_string);
	return (i);
}
