/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:17:19 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/25 01:15:04 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	is_space_or_eof(int c)
{
	return ((c == ' ' || c == '\0') || c == '\t');
}

int	isdoublequote(int c)
{
	return (c == '\"');
}

int	issinglequote(int c)
{
	return (c == '\'');
}

int	isingle_operator(char *line, int i)
{
	return ((line[i] == '>' && line[(i + 1)] != '>')
		|| (line[i] == '<' && line[(i + 1)] != '<'));
}

int	isdouble_operator(char *line, int i)
{
	return ((line[i] == '>' && line[(i + 1)] == '>')
		|| (line[i] == '<' && line[(i + 1)] == '<'));
}
