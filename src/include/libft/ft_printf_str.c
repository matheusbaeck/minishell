/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:41:12 by smagniny          #+#    #+#             */
/*   Updated: 2023/05/16 16:01:00 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{	
	int	rtn;
	int	i;

	i = -1;
	rtn = 0;
	if (!s)
	{
		rtn += write(1, "(null)", 6);
		return (rtn);
	}
	while (s[++i])
	{
		rtn += ft_putchar(s[i]);
	}
	return (rtn);
}

int	ft_printf_str(char *str)
{	
	int	rtn;

	rtn = 0;
	if (str == NULL)
		rtn += ft_putstr("(null)");
	else
		rtn += ft_putstr(str);
	return (rtn);
}
