/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:47:59 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/17 15:18:06 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	run_builtin(t_var *var)
{
	if (var->tokens == NULL || var->tokens->token == NULL)
		return (0);
	if (ft_strncmp(var->tokens->token->content, "pwd\0", 4) == 0 || ft_strncmp(var->tokens->token->content, "pwd ", 4) == 0 || ft_strncmp(var->tokens->token->content, "pwd\n", 4) == 0)
		pwd(var);
	else if (ft_strncmp(var->tokens->token->content, "env\0", 4) == 0 || ft_strncmp(var->tokens->token->content, "env ", 4) == 0 || ft_strncmp(var->tokens->token->content, "env\n", 4) == 0)
		env(var);
	
	else if (ft_strncmp(var->tokens->token->content, "cd\0", 3) == 0 || ft_strncmp(var->tokens->token->content, "cd ", 3) == 0 || ft_strncmp(var->tokens->token->content, "cd\n", 3) == 0)
		cd(var->tokens);
	else if (ft_strncmp(var->tokens->token->content, "export\0", 7) == 0 || ft_strncmp(var->tokens->token->content, "export ", 7) == 0 || ft_strncmp(var->tokens->token->content, "export\n", 7) == 0)
		export(var);
	else if (ft_strncmp(var->tokens->token->content, "echo\0", 5) == 0 || ft_strncmp(var->tokens->token->content, "echo ", 5) == 0 || ft_strncmp(var->tokens->token->content, "echo\n", 5) == 0)
		echo(var->tokens);
	else if (ft_strncmp(var->tokens->token->content, "unset\0", 6) == 0 || ft_strncmp(var->tokens->token->content, "unset ", 6) == 0 || ft_strncmp(var->tokens->token->content, "unset\n", 6) == 0)
		unset(var);
	else if (ft_strncmp(var->tokens->token->content, "clear\0", 6) == 0 || ft_strncmp(var->tokens->token->content, "clear\n", 6) == 0 || ft_strncmp(var->tokens->token->content, "clear ", 6) == 0)
		clear_history();
	else if (ft_strncmp(var->tokens->token->content, "exit\0", 6) == 0 || ft_strncmp(var->tokens->token->content, "exit\n", 6) == 0 || ft_strncmp(var->tokens->token->content, "exit ", 6) == 0)
	{
		printf("finishing on purpose\n");
		//signal(SIGTERM, handle_signal);
		exit(0);
	else
		return (1);
	return (0);
}