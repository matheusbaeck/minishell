/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer__.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:11 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 17:18:03 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	is_operator_or(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return (2);
	return (0);
}

static int	is_operator_and(char *line)
{
	if (line[0] == '&' && line[1] == '&')
		return (2);
	return (0);
}

static	int	is_operator_pipe(char *line)
{
	if (line[0] == '|' && !is_operator_or(line))
		return (1);
	return (0);
}

static	int	is_operator_bkgexec(char *line)
{
	if (line[0] == '&' && !is_operator_and(line))
		return (1);
	return (0);
}

int	is_cut_point(char *line)
{
	if (is_operator_and(line) || is_operator_or(line)
		|| is_operator_bkgexec(line) || is_operator_semicolon(line)
		|| is_operator_semicolon(line) || is_operator_grouping(line))
		return (-1);
	return (is_operator_pipe(line));
}
