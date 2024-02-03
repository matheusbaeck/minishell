/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/02 18:18:50 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../header.h"

extern int g_status;

static int	pipe_swap(int **fd_dst, int **fd_src)
{
	int	*temp;

	if (!(fd_dst && fd_src))
		return (EXIT_FAILURE);
	temp = *fd_dst;
	*fd_dst = *fd_src;
	if (temp)
	{
		free(temp);
	}
	return (EXIT_SUCCESS);
}

static int	task_child(t_var *var, int *fd_in, int *fd_out)
{
	if (fd_in) //not the first
		dup2(fd_in[0], STDIN_FILENO);
	if (var->tokens->next) //not thelast
		dup2(fd_out[1], STDOUT_FILENO);
	if (handle_redirection(var) == -1)
		perror("redir");
	if (fd_in)
		close(fd_in[1]);
	close(fd_out[0]);
	close(fd_out[1]);
	if (run_builtin_child(var, &g_status) == IS_NOT_BUILTIN)
		return (ft_exec(var));
	exit(g_status);
}

// in [1]pipe[0] [0]cmd[1] [1]pipe[0] [0]cmd2[1] [1]pipe[0] out
static int	main_task(int **fd_in, int **fd_out, void *next)
{
	if (*fd_in) // not first node
		close((*fd_in)[0]);
	close((*fd_out)[1]); // [x]fd_in[x] [x]fd_out[0]
	if (next) // not last node
	{// [x]fd_in[x] = [x]fd_out[0] ==> [x]fd_in[0]		
		pipe_swap(fd_in, fd_out);
		*fd_out = malloc(2 * sizeof(int));
		if (!(*fd_out))
			return (MALLOC_ERROR);
		if (!pipe(*fd_out))
			return (PIPE_ERROR);
	}    // [x]fd_in[0] [1]fd_out[0]
	else // last node
	{
		close((*fd_out)[0]);
		if (*fd_in)
			free(*fd_in);
		free(*fd_out);
	}
	return (EXIT_SUCCESS);
}

static int	fork_handler(t_var *var, t_list **lst)
{
	pid_t	*pid;
	int		*fd_in;
	int		*fd_out;

	fd_in = NULL;
	fd_out = malloc(2 * sizeof(int));
	pipe(fd_out);
	while (var->tokens) // [x]df_in[x] [0]cmd[1] [1]fd_out[0]
	{
		pid = malloc(sizeof(pid_t));
		*pid = fork();
		if (*pid == -1)
			exit(EXIT_FAILURE);
		else if (*pid == 0)
			task_child(var, fd_in, fd_out);
		else
		{
			ft_lstadd_back(lst, ft_lstnew((void *)pid));
			main_task(&fd_in, &fd_out, var->tokens->next);
			var->tokens = ft_lstdelone_node_getnext(var->tokens);
		}
	}
	return (EXIT_SUCCESS);
}

int	process_handler(t_var *var)
{
	t_list	*pid_list;
	t_list	*temp;

	pid_list = NULL;
	fork_handler(var, &pid_list);
	temp = pid_list;
	while (pid_list)
	{
		waitpid(*((pid_t *)(pid_list->content)), &g_status, 0);
		if (WIFEXITED(g_status))
            g_status = WEXITSTATUS(g_status);
		pid_list = pid_list->next;
	}
    ft_lstclear(&temp, &free);
	return (g_status);
}