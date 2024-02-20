/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:07:33 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/20 16:10:25 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	ms_error(char *type_err, char *err_context, int code_err)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(type_err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_context, 2);
	ft_putstr_fd("\n", 2);
	g_status = code_err;
	return (g_status);
}
