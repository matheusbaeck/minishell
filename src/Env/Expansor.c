/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:52:04 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/18 13:35:24 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	add_char(char **res, int *index, char letter)
{
	*res = (char *)my_realloc(*res, *index, (*index + 1));
	if (!*res)
		return ;
	(*res)[*index] = letter;
	(*index)++;
}

static	void	add_expansion(t_var	*var, char	*string, char	**res, int *ref, int *i)
{
	char	*expanded;
	char	*lookfor;
	int		j;
	int		end;

	j = 0;
	end = ++(*i);
	while (ft_isalpha(string[end]))
		end++;
	lookfor = ft_substr(string, *i, end - *i);
	expanded = expand(var->envp, lookfor);
	*res = (char *)my_realloc((void *) *res, \
		*ref, *ref + ft_strlen(expanded) + 1);
	if (!res)
		return ;
	while (expanded && expanded[j])
	{
		(*res)[*ref + j] = expanded[j];
		j++;
	}
	(*ref) += ft_strlen(expanded);
	free(expanded);
	free(lookfor);
	(*i) = end;
}

static	void	add_expansion_exit_status(char	**res, int *ref, int *i)
{
	char	*expanded;
	int		j;

	j = 0;
	expanded = ft_itoa(g_status);
	*res = (char *)my_realloc((void *) *res, \
		*ref, *ref + ft_strlen(expanded) + 1);
	if (!res)
		return ;
	while (expanded && expanded[j])
	{
		(*res)[*ref + j] = expanded[j];
		j++;
	}
	(*ref) += ft_strlen(expanded);
	(*i) += 2;
	free(expanded);
}

static	void	start_values_normi(int *i, int *ref, char **res)
{
	*i = 0;
	*ref = 0;
	*res = NULL;
}

//char * version instead of nodes. For integration in lexer.
void	expansor(t_var *var, char **string, int doublequoted)
{
	int		i;
	int		ref;
	char	*res;

	start_values_normi(&i, &ref, &res);
	while ((*string)[i])
	{
		if ((*string)[i] == '$')
		{
			if (ft_isalpha((*string)[i + 1]) == 0 && (*string)[i + 1] != '?')
			{
				if (doublequoted)
					add_char(&res, &ref, (*string)[i++]);
				else
					i++;
			}
			else if ((*string)[i + 1] == '?')
				add_expansion_exit_status(&res, &ref, &i);
			else
				add_expansion(var, (*string), &res, &ref, &i);
		}
		else
			add_char(&res, &ref, (*string)[i++]);
	}
	are_any_expansion(&res, string, ref);
}
