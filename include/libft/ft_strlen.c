/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:53:36 by smagniny          #+#    #+#             */
/*   Updated: 2023/11/17 19:03:42 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	index;

	if (str == NULL || str[0] == '\0')
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	ft_lendb(char **tmp)
{
	int	i;

	if (!tmp || tmp == NULL)
		return (-1);
	i = 0;
	if (tmp[i])
	{
		while (tmp[i])
			i++;
	}
	return (i);
}
