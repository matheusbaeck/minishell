/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:43:44 by math              #+#    #+#             */
/*   Updated: 2024/01/30 19:37:53 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

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

static int	task_child(t_var *var, int *fd_in, int *fd_out, int *status)
{
	(void)status;
	if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, "<", 2)
			|| ft_strncmp(var->tokens->redir->content, "<<", 3)))
	{
		if (handle_infileredirection(var) != 0)
			exit(EXIT_FAILURE);
	}
	else if (fd_in) // not first node
		dup2(fd_in[0], STDIN_FILENO);
	if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, ">", 2)
			|| ft_strncmp(var->tokens->redir->content, ">>", 3)))
	{
		if (handle_outfileredirection(var) != 0)
			exit(EXIT_FAILURE);
	}
	else if (var->tokens->next) // not last node
		dup2(fd_out[1], STDOUT_FILENO);
	if (fd_in)
	{
		if (close(fd_in[1]))
			dprintf(2, "child error: close fd_in[1]\n");
	}
	if (close(fd_out[0]))
		dprintf(2, "child error: close fd_out[0]\n");
	if (close(fd_out[1]))
		dprintf(2, "child error: close fd_out[1]\n");
	if (run_builtin_child(var) == -1)
		return (ft_exec(var));
	exit(var->exit_status);
}

// in [1]pipe[0] [0]cmd[1] [1]pipe[0] [0]cmd2[1] [1]pipe[0] out
static int	main_task(int **fd_in, int **fd_out, void *next, int *status)
{
	if (*fd_in) // not first node
	{
		if (close((*fd_in)[0]))
			dprintf(2, "main error: close fd_in[0]\n");
	}
	if (close((*fd_out)[1]))
		dprintf(2, "main error: close fd_out[1]\n");
	// [x]fd_in[x] [x]fd_out[0]
	if (next) // not last node
	{
		// [x]fd_in[x] = [x]fd_out[0] ==> [x]fd_in[0]
		*status = pipe_swap(fd_in, fd_out);
		*fd_out = malloc(2 * sizeof(int));
		if (!(*fd_out))
			return (MALLOC_ERROR);
		if (!pipe(*fd_out))
			return (PIPE_ERROR);
	}    // [x]fd_in[0] [1]fd_out[0]
	else // last node
	{
		if (close((*fd_out)[0]))
			dprintf(2, "main error: close fd_out[0]\n");
		if (*fd_in)
		{
			free(*fd_in);
		}
		free(*fd_out);
	}
	return (EXIT_SUCCESS);
}

static int	fork_handler(t_var *var, t_list **lst, int *status)
{
	pid_t	*pid;
	int		*fd_in;
	int		*fd_out;
	t_node	*node_tmp;

	fd_in = NULL;
	fd_out = malloc(2 * sizeof(int));
	pipe(fd_out);
	// [x]df_in[x] [0]cmd[1] [1]fd_out[0]
	while (var->tokens)
	{
		pid = malloc(sizeof(pid_t));
		*pid = fork();
		if (*pid == -1)
		{
			*status = FORK_ERROR;
			exit(EXIT_FAILURE);
		}
		else if (*pid == 0)
		{
			var->exit_status = task_child(var, fd_in, fd_out, status);
			exit(var->exit_status);
		}
		else
		{
			ft_lstadd_back(lst, ft_lstnew((void *)pid));
			main_task(&fd_in, &fd_out, var->tokens->next, status);
			node_tmp = var->tokens;
			var->tokens = var->tokens->next;
			ft_freenode(&node_tmp);
		}
	}
	return (EXIT_SUCCESS);
}

int	process_handler(t_var *var)
{
	t_list	*pid_list;
	t_list	*temp;
	int		status;

	pid_list = NULL;
	fork_handler(var, &pid_list, &status);
	temp = pid_list;
    status = 0;
	while (pid_list)
	{
		waitpid(*((pid_t *)(pid_list->content)), &var->exit_status, 0);
		if (WIFEXITED(status))
		{
            // Child process exited normally
            var->exit_status = WEXITSTATUS(var->exit_status);
			//printf("Child process exited with status: %i\n", var->exit_status);
			// if (WEXITSTATUS(status) == EXIT_FAILURE)
			// {
			// 	// Handle execve failure in the child process
                
			// 	//fprintf(stderr, "Child process failed to execute execve\n");
			// 	// Additional error handling or cleanup
			// }
		}
		// else if (WIFSIGNALED(status))
		// {
		// 	// Child process terminated due to a signal
		// 	//printf("Child process terminated by signal: %d\n",
		// 		WTERMSIG(status));
		// 			}
		// else
		// {
		// 	// Handle other termination conditions
		// 	//printf("Child process terminated: %d\n", WEXITSTATUS(status));
		// 			}
		pid_list = pid_list->next;
	}
    ft_lstclear(&temp, &free);
	return (var->exit_status);
}

// int	process_handler_sync(t_var *var)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid)
// 		ft_exec(var);
//     status = 0;
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		status = WEXITSTATUS(status);
// 		if (WEXITSTATUS(status) == EXIT_SUCCESS)
// 			var->tokens = var->tokens->next_success;
// 		else
// 			var->tokens = var->tokens->next_failure;
// 	}
// 	else if (WIFSIGNALED(status))
// 		{printf("Child process terminated by signal: %d\n", WTERMSIG(status)); exit (2);}
// 	else
// 		{printf("Child process terminated: %d\n", WEXITSTATUS(status)); exit (3);}
// 	return (status);
// }
