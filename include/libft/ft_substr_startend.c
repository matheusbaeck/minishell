/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_startend.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:06:36 by smagniny          #+#    #+#             */
/*   Updated: 2023/11/19 16:32:06 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_startend(char const *s, unsigned int start, unsigned int end)
{
	char	*ptr;
	size_t	len;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len || start > end)
		return (ft_strdup(""));
	len = end - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr) 
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
