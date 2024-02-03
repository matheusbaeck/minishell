/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:44:45 by math              #+#    #+#             */
/*   Updated: 2024/02/03 15:00:19 by math             ###   ########.fr       */
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
        if (*nb > INT_MAX / 10 || (*nb == INT_MAX / 10 && (*str - '0') > INT_MAX % 10 && sign == 1) ||
            *nb < INT_MIN / 10 || (*nb == INT_MIN / 10 && (*str - '0') > -(INT_MIN % 10)))
            return (1);
		*nb = (*nb * 10) + (*str - '0');
		str++;
	}
    *nb *= sign;
	return (0);
}

int is_number(char *str)
{
    int i;

    i = -1;
    if (str[0] == '+' || str[0] == '-')
        ++i;
    while (str[++i])
    {
        if (!ft_isdigit(str[i]))
            return (0);    
    }
    return (1);
}


int exit_minishell(t_var *var)
{
    int exit_val;

    if (var->tokens->redir == NULL) //&& !no_flags_supported(var->tokens->params))
    {
        //exit_val = 0;
        //dprintf(2, "atoi:%i exit:%i", ft_atoi_safe(var->tokens->params->content, &exit_val), exit_val);
        exit_val = 0;
        if (var->tokens->params)
        {
            if (var->tokens->params->next)
                return (ft_putstr_fd("Minishell: exit: too many arguments\n", 2), 1);
            if (!is_number(var->tokens->params->content) || ft_atoi_safe(var->tokens->params->content, &exit_val) || exit_val == -100)
            {   
                ft_putstr_fd("Minishell: exit: Illegal number: ", 2);
                ft_putstr_fd(var->tokens->params->content, 2);
                ft_putstr_fd("\n", 2);
                if (exit_val == -100)
                    return (156);
                return (2);
            }
        }
        if (var->tokens->next)
            return (0);
        ft_lstclear_node(&var->tokens);
        ft_freeenv(&var->envp);
        exit (exit_val);
    }
    return (0);
}
