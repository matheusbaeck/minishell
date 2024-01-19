/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:41:12 by smagniny          #+#    #+#             */
/*   Updated: 2022/12/12 18:20:29 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_int(int num)
{
	int		rtn;

	rtn = 0;
	if (num == 0)
		rtn += write(1, "0", 1);
	else
		rtn += ft_itoalcount(num);
	return (rtn);
}
