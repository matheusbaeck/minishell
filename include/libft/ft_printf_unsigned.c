/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:34:45 by smagniny          #+#    #+#             */
/*   Updated: 2022/12/12 18:20:37 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_unsigned(unsigned int num)
{
	int		rtn;

	rtn = 0;
	if (num == 0)
		rtn += ft_putchar('0');
	else
		rtn += ft_utoa(num);
	return (rtn);
}
