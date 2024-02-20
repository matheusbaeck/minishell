/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addword.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:30:13 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 16:06:34 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	remove_previous_dollar_expansion_ifneeded(char **token_string)
{
	if (*token_string && ft_strncmp((*token_string), "$", 1) == 0)
	{
		free((*token_string));
		(*token_string) = NULL;
	}
}

static	char	*skipquotes(char **token_string, int *i, int *start)
{
	(*i)++;
	*start = (*start) + 2;
	return ((*token_string));
}

char	*check_word_rec(t_var *var, int *start, int *i, char *str)
{
	char	*upd_token_string;

	upd_token_string = NULL;
	if (isdoublequote(var->inputline[*i]))
	{
		remove_previous_dollar_expansion_ifneeded(&str);
		if (isdoublequote(var->inputline[++(*i)]))
			upd_token_string = skipquotes(&str, i, start);
		else
			upd_token_string = ft_strjoinfreee(str, getstr_dbq(var, i, start));
	}
	else if (issinglequote(var->inputline[*i]))
	{
		remove_previous_dollar_expansion_ifneeded(&str);
		if (issinglequote(var->inputline[++(*i)]))
			upd_token_string = skipquotes(&str, i, start);
		else
			upd_token_string = ft_strjoinfreee(str, getstr_sq(var, i, start));
	}
	else
		upd_token_string = ft_strjoinfreee(str, get_word(var, i, start));
	return (upd_token_string);
}
