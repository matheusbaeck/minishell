/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:53:11 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/14 15:39:07 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	*my_realloc(void *ptr, size_t originalLength, size_t newLength)
{
	void	*ptrnew;

	ptrnew = NULL;
	if (newLength == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (calloc(newLength, sizeof(char)));
	else if (newLength <= originalLength)
		return (ptr);
	else
	{
		ptrnew = calloc(newLength, sizeof(char));
		if (ptrnew)
		{
			memcpy(ptrnew, ptr, originalLength);
			free(ptr);
		}
		return (ptrnew);
	}
}

//given USER returns LOGNAME of current machine
char	*expand(t_env *env, char *dollar_str)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	str = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->line_env, dollar_str, ft_strlen(dollar_str)) == 0)
		{
			str = ft_strdup(ft_strrchr(tmp->line_env, '=') + 1);
			return (str);
		}
		tmp = tmp->next;
	}
    //printear mensaje de error con que no ha encontrado la variable en las var de entorno
	return (NULL);
}

static	void	close_string_expansion(char **res, int ref)
{
	*res = (char *)my_realloc(*res, ref, (ref + 1) * sizeof(char));
	if (!res)
		return ;
	(*res)[ref] = '\0';
}

void	are_any_expansion(char **res, char **string, int ref)
{
	if (*res != NULL)
		close_string_expansion(res, ref);
	if (*res == NULL || !(*res) || strcmp((*string), *res) == 0)
	{
		//printf("[%s] no hay expansión\n", (*string));
		free(*res);
		return ;
	}
	else
	{
		//printf("[%s] -->expansión--> [%s]\n", (*string), res);
		free((*string));
		(*string) = (*res);
	}
}
