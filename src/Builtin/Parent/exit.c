/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:44:45 by math              #+#    #+#             */
/*   Updated: 2024/02/20 17:01:28 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

static int	ft_atoi_safe(const char *str, int *nb)
{
	int	sign;

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
		if (*nb > INT_MAX / 10
			|| (*nb == INT_MAX / 10 && (*str - '0') > INT_MAX % 10 && sign == 1)
			|| *nb < INT_MIN / 10
			|| (*nb == INT_MIN / 10 && (*str - '0') > -(INT_MIN % 10)))
			return (1);
		*nb = (*nb * 10) + (*str - '0');
		str++;
	}
	*nb *= sign;
	return (0);
}

static int	check_multi_params(t_subnode *params_next)
{
	if (params_next)
		return (ft_putstr_fd("Minishell: exit: too many arguments\n", 2), 1);
	return (0);
}

static	int	is_number(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		++i;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static	int	exit_error(t_subnode *params, int exit_val)
{
	if (is_number(params->content))
		ft_putstr_fd("Minishell: exit: numeric argument required\n", 2);
	else
	{
		ft_putstr_fd("Minishell: exit: Illegal number:", 2);
		ft_putstr_fd(params->content, 2);
		ft_putstr_fd("\n", 2);
	}
	if (exit_val < 0)
		return (exit_val % 256);
	return (2);
}

int	exit_minishell(t_var *var)
{
	int	exit_val;

	if (var->tokens->redir == NULL)
	{
		exit_val = 0;
		if (var->tokens->params)
		{
			if (check_multi_params(var->tokens->params->next))
				return (1);
			if (is_number(var->tokens->params->content)
				|| ft_atoi_safe(var->tokens->params->content, &exit_val)
				|| exit_val < 0)
				return (exit_error(var->tokens->params, exit_val));
		}
		if (var->tokens->next)
			return (0);
		ft_lstclear_node(&var->tokens);
		ft_freeenv(&var->envp);
		write(1, "exit\n", 5);
		exit(exit_val);
	}
	return (0);
}
