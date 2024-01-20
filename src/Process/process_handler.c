/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:43:44 by math              #+#    #+#             */
/*   Updated: 2024/01/19 18:11:51 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

// static void    print_pipe(int fd[2])
// {
//     char    buffer;

//     while (read(fd[0], &buffer, 1) > 0)
//     {
//         write(1, &buffer, 1);
//     }
// }

int    process_handler(t_var *var)
{
    pid_t   pid;
    pid_t   last_pid;
    int     *fd_in;
    int     *fd_out;
    int     *temp;
	t_node	*node_tmp;
    int		status;
	int		last_status;

    fd_in = malloc(2 * sizeof(int));
    fd_out = malloc(2 * sizeof(int));
    pipe(fd_in);
	pipe(fd_out);
    while (var->tokens)
	{
		pid = fork();
		if (pid == 0)
		{
            dprintf(2, "child\n");
            if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, "<", 2) || ft_strncmp(var->tokens->redir->content, "<<", 3)))
            {
                if (handle_infileredirection(var) != 0)
                    return (EXIT_FAILURE);
            }
            else
                dup2(fd_in[0], STDIN_FILENO);
            if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, ">", 2) || ft_strncmp(var->tokens->redir->content, ">>", 3)))
            {
                if (handle_outfileredirection(var) != 0)
                    return (EXIT_FAILURE);
            }
            else if (var->tokens->next)
                dup2(fd_out[1], STDOUT_FILENO);
            close(fd_in[0]);
            close(fd_in[1]);
            close(fd_out[0]);
            close(fd_out[1]);
			if (run_builtin(var))
				exit(ft_exec(var));
            printf("DANGER!!!\n");
            exit(0);
		}
        else
        {
		    close(fd_in[0]);
		    close(fd_in[1]);
            close(fd_out[1]);
            temp = fd_in;
		    fd_in = fd_out;
            free(temp);
            fd_out = malloc(2 * sizeof(int));
            pipe(fd_out);
			node_tmp = var->tokens;
            var->tokens = var->tokens->next;
			ft_freenode(&node_tmp);
            if (!var->tokens)
                last_pid = pid;
        }
    }
    last_status = 0;
	while (var->nb_node--)
	{
		pid = waitpid(-1, &status, 0);
		printf("Pid [%d] has finished w status: %d && errno=%d\n", pid, status,errno);
		if (pid == last_pid)
			last_status = status;
		if (pid == -1)
		{
			//close(fd[0][1]);
			//free_all
			printf("last process WEXITSTATUS: %d\n", WEXITSTATUS(last_status));
			return (WEXITSTATUS(last_status));
		}
	}
	free(fd_in);
	free(fd_out);
    // waitpid(0, NULL, 0);
    // close(fd_in[1]);
    // // print_pipe(fd_in);
    // close(fd_in[0]);
    return (0);
}
