/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:20:34 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_digit_count(long long int i)
{
	int	count;

	count = 0;
	if (i < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

int	ft_itoalcount(int k)
{
	char			*str;
	int				rtn;
	int				i;

	i = ft_digit_count(k);
	rtn = i;
	if (k == (-2147483647 - 1))
		return (ft_putstr("-2147483648"));
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!(str))
		return (0);
	str[i--] = '\0';
	if (k < 0)
	{
		str[0] = '-';
		k = k * -1;
	}
	while (k > 0)
	{
		str[i--] = k % 10 + '0';
		k = k / 10;
	}
	ft_putstr(str);
	free(str);
	return (rtn);
}

int	ft_utoa(unsigned long k)
{	
	char			*str;
	int				rtn;
	int				i;

	i = ft_digit_count(k);
	rtn = i;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!(str))
		return (0);
	str[i--] = '\0';
	if ((int)k < 0)
	{
		str[0] = '-';
		k = k * -1;
	}
	while (k > 0)
	{
		str[i--] = k % 10 + '0';
		k = k / 10;
	}
	ft_putstr(str);
	free(str);
	return (rtn);
}

int	ft_putnbrbase(unsigned long int nb, char *base, int *rtn)
{
	unsigned int	len;

	len = ft_strlen(base);
	if (nb < len)
		*rtn += ft_putchar(base[nb]);
	if (nb >= len)
	{
		ft_putnbrbase(nb / len, base, rtn);
		ft_putnbrbase(nb % len, base, rtn);
	}
	return (*rtn);
}
