/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addword.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:30:13 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/07 22:33:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static	void	remove_previous_dollar_expansion_ifneeded(char **token_string)
{
	if (*token_string && ft_strncmp((*token_string), "$", 1) == 0)
	{
		free((*token_string));
		printf("borrado $ anterior pk habian comillas despues perro\n");
		(*token_string) = NULL;
	}
}

static	char	*skipquotes(char **token_string, int *i, int *start)
{
	(*i)++;
	*start = (*start) + 2;
	return ((*token_string));
}

char	*check_word_rec(t_var *var, int *start, int *i, char *token_string)
{
	char	*upd_token_string;

	upd_token_string = NULL;
	if (isdoublequote(var->inputline[*i]))// si te encuentras una comilla.
	{
		// erasing $ if next char is quotes (Remember you are expanding on the fly)
		remove_previous_dollar_expansion_ifneeded(&token_string);
		if (isdoublequote(var->inputline[++(*i)]))
			upd_token_string = skipquotes(&token_string, i, start);
		else
			upd_token_string = ft_strjoinfreee(token_string, get_str_doublequoted(var, i, start)); //recuperar la string entre comillas dobles. y concatenar con la palabra anterior si estaba pegada al quote y pone el iterador en la posicion siguiente
	}
	else if (issinglequote(var->inputline[*i]))
	{
		remove_previous_dollar_expansion_ifneeded(&token_string);
		if (issinglequote(var->inputline[++(*i)]))
			upd_token_string = skipquotes(&token_string, i, start);
		else
			upd_token_string = ft_strjoinfreee(token_string, get_str_singlequoted(var, i, start));//recuperar la string entre comillas simples. y concatenar con la palabra anterior si estaba pegada al quote y pone el iterador en la posicion siguiente
	}
	else
		upd_token_string = ft_strjoinfreee(token_string, get_word(var,i, start));
	return (upd_token_string);
}
