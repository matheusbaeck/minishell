/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:43:44 by math              #+#    #+#             */
/*   Updated: 2024/01/19 20:38:17 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static int handleInFileRedirection(void)
{
    return (0);
}

static int handleOutFileRedirectionl(void)
{
    return (0);
}

static void task_child(t_var *var, int *fd_in, int *fd_out) //check for error handle
{
    if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, "<", 2) || ft_strncmp(var->tokens->redir->content, "<<", 3)))
    {
        if (handleInFileRedirection() != 0)
            exit (EXIT_FAILURE);
    }
    else
        dup2(fd_in[0], STDIN_FILENO);
    if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, ">", 2) || ft_strncmp(var->tokens->redir->content, ">>", 3)))
    {
        if (handleOutFileRedirectionl() != 0)
            exit (EXIT_FAILURE);
    }
    else if (var->tokens->next)
        dup2(fd_out[1], STDOUT_FILENO);
    close(fd_in[0]);
    close(fd_in[1]);
    close(fd_out[0]);
    close(fd_out[1]);
    if (run_builtin(var))
        ft_exec(var);
    printf("DANGER!!!\n");
    exit (127);
}

static void main_task(t_var *var, int **fd_in, int **fd_out)
{
    int     *temp;

    close((*fd_in)[0]);
    close((*fd_in)[1]);
    close((*fd_out)[1]);
    temp = *fd_in;
    *fd_in = *fd_out;
    *fd_out = malloc(2 * sizeof(int)); //malloc protection
    free(temp);
    pipe(*fd_out); // pipe protection
    var->tokens = var->tokens->next;
}

static void	fork_handler(t_var *var, t_list **lst)
{
    pid_t child_pid;
    int     *fd_in;
    int     *fd_out;

    fd_in = malloc(2 * sizeof(int)); // mallocs and pipes protection
    fd_out = malloc(2 * sizeof(int));
    pipe(fd_in);
	pipe(fd_out); 

    while (var->tokens)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork fail");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0)
        {
            task_child(var, fd_in, fd_out);
        }
        else
        {
            ft_lstadd_back(lst, ft_lstnew((void *)&child_pid));
            main_task(var, &fd_in, &fd_out);
        }
    }
}

int    process_handler(t_var *var)
{
    t_list  *pid;
    int		status;

    //pid = malloc(sizeof(t_list));
    while (var->tokens)
		fork_handler(var, &pid);
	while (pid)
	{
		waitpid(*((pid_t *)pid->content), &status, 0);
        WEXITSTATUS(status);
		pid = pid->next;
	}
    ft_lstclear(&pid, NULL); //verify that function acept NULL as param
    free(pid);
    // close(fd_in[1]); free all data
    // close(fd_in[0]);
    return (0);
}

// static void    print_pipe(int fd[2])
// {
//     char    buffer;

//     while (read(fd[0], &buffer, 1) > 0)
//     {
//         write(1, &buffer, 1);
//     }
// }
