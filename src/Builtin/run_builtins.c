/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:47:59 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/25 03:17:14 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	run_builtin_child(t_var *var)
{
	int	ret_value;

	ret_value = 0;
	if (var->tokens == NULL || var->tokens->token == NULL)
		return (ret_value);
	if (ft_strncmp(var->tokens->token->content, "pwd\0", 4) == 0)
		pwd(var);
	else if (ft_strncmp(var->tokens->token->content, "env\0", 4) == 0)
		env(var);
	else if (ft_strncmp(var->tokens->token->content, "echo\0", 5) == 0)
		echo(var->tokens);
	return (ret_value);
}

int	run_builtin_parent(t_var *var)
{
	int	ret_value;

	ret_value = 0;
	if (var->tokens == NULL || var->tokens->token == NULL)
		return (0);
	else if (ft_strncmp(var->tokens->token->content, "cd\0", 3) == 0)
		ret_value = cd(var->tokens);
	else if (ft_strncmp(var->tokens->token->content, "export\0", 7) == 0)
		ret_value = export(var);
	else if (ft_strncmp(var->tokens->token->content, "unset\0", 6) == 0)
		ret_value = unset(var);
	else if (ft_strncmp(var->tokens->token->content, "clear\0", 6) == 0)
		clear_history();
	else if (ft_strncmp(var->tokens->token->content, "exit\0", 5) == 0)
		ret_value = exit_minishell(var);
	return (ret_value);
}
