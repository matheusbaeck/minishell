/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:52:04 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 16:45:54 by smagniny         ###   ########.fr       */
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

static	char	*expd(t_env *envp, char *string, int *i)
{
	char	*expanded;
	char	*lookfor;
	int		end;

	end = ++(*i);
	while (ft_isalpha(string[end]))
		end++;
	lookfor = ft_substr(string, *i, end - *i);
	expanded = expand(envp, lookfor);
	free(lookfor);
	(*i) = end;
	return (expanded);
}

static	void	add_expansion(char	*expanded, char	**res, int *ref)
{
	int		j;

	j = 0;
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
				add_expansion(expd(var->envp, *string, &i), &res, &ref);
		}
		else
			add_char(&res, &ref, (*string)[i++]);
	}
	are_any_expansion(&res, string, ref);
}
