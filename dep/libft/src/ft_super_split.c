/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:26:40 by math              #+#    #+#             */
/*   Updated: 2024/01/26 14:27:22 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_words(char const *s, char *delimiters)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		while (ft_strchr(delimiters, s[i]))
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] && !ft_strchr(delimiters, s[i]))
			i++;
	}
	return (nb);
}

static char	*ft_place_word(char const *s, char *delimiters)
{
	char	*word;
	int		i;
	int		len;

	len = 0;
	while (s[len] && !ft_strchr(delimiters, s[len]))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	*ft_cpy_str(int i, char const *s, char *delimiters, char **res)
{
	res[i] = ft_place_word(s, delimiters);
	if (!res[i])
	{
		while (i > 0)
		{
			i--;
			free(res[i]);
		}
		free(res);
		return (NULL);
	}
	return (res[i]);
}

char	**super_split(char const *s, char *delimiters)
{
	int		nb_words;
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	i = 0;
	nb_words = ft_count_words(s, delimiters);
	res = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!res)
		return (NULL);
	while (i < nb_words)
	{
		while (ft_strchr(delimiters, *s))
			s++;
		if (*s != '\0')
			res[i] = ft_cpy_str(i, s, delimiters, res);
		while (*s && !ft_strchr(delimiters, *s))
			s++;
		i++;
	}
	res[i] = 0;
	return (res);
}
