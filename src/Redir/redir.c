/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:03:39 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/22 17:19:32 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	base_redir(t_var *var)
{
	if (var->fd_in)
	{
		close(var->fd_in);
		dup2(var->std_in, 0);
		close(var->std_in);
	}
	if (var->fd_out)
	{
		close(var->fd_out);
		dup2(var->std_out, 1);
		close(var->std_out);
	}
}

int		handle_outfileredirection(t_var *var)
{
	t_node		*tmp;
	t_subnode	*sub_redir_tmp;
	t_subnode	*sub_wheredir_tmp;

	tmp = var->tokens;
	if (!tmp || tmp->redir == NULL || tmp->where_redir == NULL)
		return (0);
	sub_redir_tmp = var->tokens->redir;
	sub_wheredir_tmp = var->tokens->where_redir;
	var->std_out = dup(STDOUT_FILENO);
	while (sub_redir_tmp && sub_wheredir_tmp)
	{
		if (sub_redir_tmp->content == NULL || sub_wheredir_tmp->content == NULL)
			return (0);
		//printf("redir executed: %s\nWhere_file founded: %s\n", sub_redir_tmp->content, sub_wheredir_tmp->content);
		if (ft_strncmp(sub_redir_tmp->content, ">>", 2) == 0)
		{
			var->fd_out = open(sub_wheredir_tmp->content, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (!var->fd_out)
				printf("Minishell: %s: %s\n", \
					strerror(errno),sub_wheredir_tmp->content);
			dup2(var->fd_out, STDOUT_FILENO);
			close(var->fd_out);
		}
		else if (ft_strncmp(sub_redir_tmp->content, ">", 1) == 0 )
		{
			var->fd_out = open(sub_wheredir_tmp->content, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (!var->fd_out)
				printf("Minishell: %s: %s\n", \
					strerror(errno),sub_wheredir_tmp->content);
			dup2(var->fd_out, STDOUT_FILENO);
			close(var->fd_out);
		}
		sub_redir_tmp = sub_redir_tmp->next;
		sub_wheredir_tmp = sub_wheredir_tmp->next;
	}
	return (0);
}

int		handle_infileredirection(t_var *var)
{
	t_subnode	*sub_redir_tmp;
	t_subnode	*sub_wheredir_tmp;

	sub_redir_tmp = var->tokens->redir;
	sub_wheredir_tmp = var->tokens->where_redir;
	if (sub_redir_tmp == NULL || sub_wheredir_tmp == NULL)
		return (0);
	var->std_in = dup(STDIN_FILENO);
	while (sub_redir_tmp && sub_wheredir_tmp)
	{
		if (sub_redir_tmp->content == NULL || sub_wheredir_tmp->content == NULL)
			return (0);
		if (ft_strncmp(sub_redir_tmp->content, "<<", 3) == 0)
			printf("Esperate pillín aun no estoy listo para preguntarte lo que sea con un heredoc\n");
			// redirect_input(var, sub_redir_tmp->content, O_APPEND);
		else if (ft_strncmp(sub_redir_tmp->content, "<", 2) == 0)
		{
			var->fd_in = open(sub_wheredir_tmp->content, O_RDONLY);
			if (!var->fd_in)
			{	
				printf("Minishell: %s: %s\n", \
					strerror(errno),sub_wheredir_tmp->content);
				return (var->fd_out);
			}
			dup2(var->fd_in, STDIN_FILENO);
			close(var->fd_in);
		}
		sub_redir_tmp = sub_redir_tmp->next;
		sub_wheredir_tmp = sub_wheredir_tmp->next;
	}
	return (0);
}

int		redir(t_var *var)
{
	if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, "<", 2) || ft_strncmp(var->tokens->redir->content, "<<", 3)))
	{
		if (handle_infileredirection(var) != 0)
		{
			printf("error on handle_infile_builtin: %d\n", EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
	}
	if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, ">", 2) || ft_strncmp(var->tokens->redir->content, ">>", 3)))
	{
		if (handle_outfileredirection(var) != 0)
		{
			printf("error on handle_outfile_builtin: %d\n", EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
	}
	return (0);
}