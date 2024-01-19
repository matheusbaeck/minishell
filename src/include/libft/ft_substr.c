/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:37:05 by smagniny          #+#    #+#             */
/*   Updated: 2022/09/27 17:20:27 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		k;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup("\0"));
	k = ft_strlen(s + start);
	if (k < len)
		len = k;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ptr))
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

/*
int	main(void)
{
	char tab[] = "holacomoestasmanu";
	char *p;

	p = ft_substr(tab,0,120);
	printf("%s", p);
	free(p);
}*/