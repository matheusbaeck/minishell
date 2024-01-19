/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:54:29 by smagniny          #+#    #+#             */
/*   Updated: 2022/09/23 15:25:29 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if ((d < s) && len)
	{
		ft_memcpy(d, s, len);
	}
	else if ((d > s) && len)
	{
		while (len--)
		{
			d[len] = s[len];
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main(void) {
   	char dest[] = "H";
	char src[]  = "kkkkkkk";
    char dest1[] = "H";
	char src1[]  = "kkkkkkk";
  	printf("Before memmove dest = %s, src = %s\n", dest, src);
    ft_memmove(dest, src, 2);
   	printf("After memmove dest = %s, src = %s\n", dest, src);

    printf("memmove dest = %s, src = %s\n", dest1, src1);
    memmove(dest1, src1, 2);
   	printf("A memmove dest = %s, src = %s\n", dest1, src1);

  	return(0);
}*/
