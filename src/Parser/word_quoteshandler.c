/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_quoteshandler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:54:42 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 23:23:54 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

char	*ft_strjoinfreee(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s2 && !s1)
		return (0);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (0);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (new_str);
}

char	*get_word(t_var *var, int *i, int *start)
{
	char	*str;

	str = NULL;
	if (*i >= var->len_inputline)
		return (NULL);
	while (ft_isascii(var->inputline[*i])
		&& (!isdoublequote(var->inputline[*i])
			&& !issinglequote(var->inputline[*i])
			&& !is_space_or_eof(var->inputline[*i])
			&& !isingle_operator(var->inputline, *i)
			&& !isdouble_operator(var->inputline, *i)))
		(*i)++;
	if (*start < *i)
	{
		str = ft_substr(var->inputline, *start, *i - *start);
		if (*str)
			expansor(var, &str, 0);
	}
	*start = *i;
	return (str);
}

char	*getstr_dbq(t_var *var, int *i, int *start)
{
	char	*token_string;

	token_string = NULL;
	(*start)++;
	(*i)++;
	while (*i <= var->len_inputline && ft_isascii(var->inputline[*i])
		&& !isdoublequote(var->inputline[*i]))
		(*i)++;
	if (*i >= var->len_inputline)
		return (ms_error("Syntax error", "unexpected end of file", 2), NULL);
	if (*start != *i && *start < *i)
	{
		token_string = ft_substr(var->inputline, *start, (*i - *start));
		if (*token_string)
			expansor(var, &token_string, 1);
	}
	*start = ++(*i);
	return (token_string);
}

char	*getstr_sq(t_var *var, int *i, int *start)
{
	char	*token_string;

	token_string = NULL;
	(*start)++;
	(*i)++;
	while (*i <= var->len_inputline && ft_isascii(var->inputline[*i])
		&& !issinglequote(var->inputline[*i]))
		(*i)++;
	if (*i >= var->len_inputline)
		return (ms_error("Syntax error", "unexpected end of file", 2), NULL);
	if (*start != *i && *start < *i)
		token_string = ft_substr(var->inputline, *start, (*i - *start));
	*start = ++(*i);
	return (token_string);
}
