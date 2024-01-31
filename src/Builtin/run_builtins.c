/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:47:59 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/29 15:29:02 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	run_builtin_child(t_var *var)
{
	if (var->tokens == NULL || var->tokens->token == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(var->tokens->token->content, "pwd\0", 4) == 0)
		var->exit_status = pwd(var);
	else if (ft_strncmp(var->tokens->token->content, "env\0", 4) == 0)
		var->exit_status = env(var);
	else if (ft_strncmp(var->tokens->token->content, "echo\0", 5) == 0)
		var->exit_status = echo(var->tokens);
	else
		return (-1);
	return (var->exit_status);
}

int	run_builtin_parent(t_var *var)
{

	if (var->tokens == NULL || var->tokens->token == NULL)
		return (0);
	else if (ft_strncmp(var->tokens->token->content, "cd\0", 3) == 0)
	{
		if (handle_redirection(var) == -1)
			perror("redir\n");
		return(cd(var->tokens));
	}
	else if (ft_strncmp(var->tokens->token->content, "export\0", 7) == 0)
	{
		if (handle_redirection(var) == -1)
			perror("redir\n");
		return(export(var));
	}
	else if (ft_strncmp(var->tokens->token->content, "unset\0", 6) == 0)
	{
		if (handle_redirection(var) == -1)
			perror("redir\n");
		return (unset(var));
	}
	else if (ft_strncmp(var->tokens->token->content, "clear\0", 6) == 0)
	{	
		clear_history();
		return (0);
	}
	else if (ft_strncmp(var->tokens->token->content, "exit\0", 5) == 0)
		return(exit_minishell(var));
	else
		return (1);

}
