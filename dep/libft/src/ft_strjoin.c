/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:48:06 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str || (!s1 && !s2))
		return (0);
	i = 0;
	while (s1 && s1[i] && s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoinfrees2(char const *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str || (!s1 && !s2))
		return (0);
	i = 0;
	while (s1 && s1[i] && s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	if (s2)
		free(s2);
	return (new_str);
}

/*
int	main(void)
{
	char tab[] = "hola";
	char tabb[] = "adios";
	char *p;

	p = ft_strjoin(tab, tabb);
	printf("%s",p);
	free(p);
}*/