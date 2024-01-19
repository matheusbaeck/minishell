/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isword.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:09:22 by smagniny          #+#    #+#             */
/*   Updated: 2023/06/13 18:08:59 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isword(const char *string, const char *substring)
{
	size_t	string_len;
	size_t	substring_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	string_len = ft_strlen(string);
	substring_len = ft_strlen(substring);
	if (string_len < substring_len)
		return (0);
	while (i <= string_len - substring_len)
	{
		while (j < substring_len)
		{
			if (string[i + j] != substring[j])
				break ;
			j++;
		}
		if (j == substring_len)
			return (1);
		i++;
	}
	return (0);
}
