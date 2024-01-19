/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:08:34 by smagniny          #+#    #+#             */
/*   Updated: 2022/12/12 18:20:47 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_eval_format(const char *str, va_list p, int index)
{	
	int	n;

	n = 0;
	if (str[index] == '%')
		n += write(1, "%", 1);
	if (str[index] == 'c')
		n += ft_printf_char(va_arg(p, int));
	if (str[index] == 's')
		n += ft_printf_str(va_arg(p, char *));
	if (str[index] == 'd' || str[index] == 'i')
		n += ft_printf_int(va_arg(p, int));
	if (str[index] == 'u')
		n += ft_printf_unsigned(va_arg(p, unsigned long int));
	if (str[index] == 'p')
	{
		n += write(1, "0x", 2);
		ft_putnbrbase(va_arg(p, unsigned long int), "0123456789abcdef", &n);
	}
	if (str[index] == 'x')
		ft_putnbrbase(va_arg(p, unsigned int), "0123456789abcdef", &n);
	if (str[index] == 'X')
		ft_putnbrbase(va_arg(p, unsigned int), "0123456789ABCDEF", &n);
	return (n);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	va_list	params;
	int		n;

	i = -1;
	n = 0;
	va_start(params, str);
	while (str[++i])
	{	
		if (str[i] == '%')
		{	
			i++;
			n += ft_eval_format(str, params, i);
		}
		else
			n += write(1, &str[i], 1);
	}
	va_end(params);
	return (n);
}
