/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:06:33 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *dst, const char *str, size_t len)
{
	unsigned long	i;
	int				j;

	j = 0;
	i = 0;
	if (str[0] == '\0')
		return ((char *)dst);
	while (len && dst[i])
	{
		j = 0;
		while (dst[i] == str[j] && dst[i] && i < len)
		{
			i++;
			j++;
		}
		if (!str[j])
			return ((char *)&dst[i - j]);
		i = (i - j) + 1;
	}
	return (0);
}
