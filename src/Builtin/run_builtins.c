/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:47:59 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/20 12:40:59 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	run_builtin_child(t_var *var, int *last_status)
{
	if (var->tokens == NULL || var->tokens->token == NULL)
		return (IS_NOT_BUILTIN);
	else if (!ft_strncmp(var->tokens->token->content, "pwd\0", 4))
		*last_status = pwd(var);
	else if (!ft_strncmp(var->tokens->token->content, "env\0", 4))
		*last_status = env(var);
	else if (!ft_strncmp(var->tokens->token->content, "echo\0", 5))
		*last_status = echo(var->tokens);
	else
		return (IS_NOT_BUILTIN);
	return (IS_BUILTIN);
}

static	int	check_builtin(t_var *var, int *last_status)
{
	if (!ft_strncmp(var->tokens->token->content, "cd\0", 3))
	{
		if (handle_redirection(var) == -1)
			perror("redir\n");
		*last_status = cd(var->tokens);
		return (IS_BUILTIN);
	}
	else if (!ft_strncmp(var->tokens->token->content, "export\0", 7))
	{
		if (handle_redirection(var) == -1)
			perror("redir\n");
		*last_status = export(var);
		return (IS_BUILTIN);
	}
	else if (!ft_strncmp(var->tokens->token->content, "unset\0", 6))
	{
		if (handle_redirection(var) == -1)
			perror("redir\n");
		*last_status = unset(var);
		return (IS_BUILTIN);
	}
	return (IS_NOT_BUILTIN);
}

int	run_builtin_parent(t_var *var, int *last_status)
{
	if (var->tokens == NULL || var->tokens->token == NULL)
		return (IS_NOT_BUILTIN);
	else if (!ft_strncmp(var->tokens->token->content, "clear\0", 6))
		clear(var);
	else if (!ft_strncmp(var->tokens->token->content, "exit\0", 5))
		*last_status = exit_minishell(var);
	else if (check_builtin(var, last_status))
		return (IS_BUILTIN);
	else
		return (IS_NOT_BUILTIN);
	return (IS_BUILTIN);
}
