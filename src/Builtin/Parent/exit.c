/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:44:45 by math              #+#    #+#             */
/*   Updated: 2024/02/01 21:06:10 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

static int	ft_atoi_safe(const char *str, int *nb)
{
	int sign;

	sign = 1;
	*nb = 0;
	while (*str == ' ' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == '\v')
		str++;
    if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
        if (nb < 214748364 && sign == 1 && (int)(*str - '0') > 7)
            return (1);
        else if (nb < 214748364 && sign == -1 && (int)(*str - '0') > 8)
            return (1);
		*nb = (*nb * 10) + (*str - '0');
		str++;
	}
    nb = sign * *nb;
	return (0);
}


int exit_minishell(t_var *var)
{
    int exit_val;

    
    if (var->tokens->flags == NULL
        && var->tokens->redir == NULL)
    {
        if (var->tokens->params == NULL)
            exit_val = 0;
        else
            if (ft_atoi_safe(*((int *)(var->tokens->params->content)), &exit_val) == -1)
            {   
                ft_putstr_fd(2, "1: exit: Illegal number:\n");
                var->exit_status = 2;
                return (1);
            }
        ft_lstclear_node(&var->tokens);
        free(var->tokens);
        ft_freeenv(&var->envp);
        exit (exit_val);
    }
    return (0);
}