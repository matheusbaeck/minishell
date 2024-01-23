/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:43:44 by math              #+#    #+#             */
/*   Updated: 2024/01/23 17:28:01 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static int task_child(t_var *var, int *fd_in, int *fd_out, int *status) //check for error handle
{
    (void)status;
    if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, "<", 2) || ft_strncmp(var->tokens->redir->content, "<<", 3)))
    {
        if (handle_infileredirection(var) != 0)
            exit (EXIT_FAILURE);
    }
    else
        dup2(fd_in[0], STDIN_FILENO);
    if (var->tokens->redir && (ft_strncmp(var->tokens->redir->content, ">", 2) || ft_strncmp(var->tokens->redir->content, ">>", 3)))
    {
        if (handle_outfileredirection(var) != 0)
            exit (EXIT_FAILURE);
    }
    else if (var->tokens->next)
        dup2(fd_out[1], STDOUT_FILENO);
    dup2(fd_in[0], STDIN_FILENO);
    if (var->tokens->next)
        dup2(fd_out[1], STDOUT_FILENO);
    if (close(fd_in[0]))
        dprintf(2, "child error: close fd_in[0]\n");
    if(close(fd_in[1]))
        dprintf(2, "child error: close fd_in[1]\n");
    if (close(fd_in[0]))
        dprintf(2, "child error: close fd_out[0]\n");
    if(close(fd_in[1]))
        dprintf(2, "child error: close fd_out[1]\n");
    if (!run_builtin(var))
        exit (0);
    return(ft_exec(var));
}

static int main_task(int **fd_in, int **fd_out, void *next, int *status)
{
    int     *temp;

    if (close((*fd_in)[1]))
        dprintf(2, "main error: close fd_in[0]\n");
    if(close((*fd_in)[0]))
        dprintf(2, "main error: close fd_in[1]\n");
    if (close((*fd_out)[1]))
            dprintf(2, "main error: close fd_out[1]\n");
    if (!next)
    {
        if (close((*fd_out)[0]))
            dprintf(2, "main error: close fd_out[1]\n");
    }
    temp = *fd_in;
    *fd_in = *fd_out;
    *fd_out = malloc(2 * sizeof(int));
    if (!(*fd_out))
        return (MALLOC_FAIL);
    *status = pipe(*fd_out);
    if (!(*status))
        return (PIPE_FAIL);
    free(temp);
    return (EXIT_SUCCESS);
}

static int	fork_handler(t_var *var, t_list **lst, int *status)
{
    pid_t   pid;
    int     *fd_in;
    int     *fd_out;
    t_node  *node_tmp;

    fd_in = malloc(2 * sizeof(int)); // mallocs and pipes protection
    fd_out = malloc(2 * sizeof(int));
    pipe(fd_in);
	pipe(fd_out);

    while (var->tokens)
    {
        pid = fork();
        if (pid == -1)
        {
            *status = FORK_FAIL;
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            task_child(var, fd_in, fd_out, status);
            printf("DANGER\n");
            free(fd_in);
            free(fd_out);
            exit(127);
        }
        else
        {
            ft_lstadd_back(lst, ft_lstnew((void *)&pid));
            main_task(&fd_in, &fd_out, var->tokens->next, status);
            node_tmp = var->tokens;
            var->tokens = var->tokens->next;
            ft_freenode(&node_tmp);
        }
    }
    if (close(fd_in[0]))
        dprintf(2, "forking error: close fd_in[0]\n");
    if(close(fd_out[0]))
    if (close(fd_out[1]))
        dprintf(2, "forking error: close fd_out[0]\n");
    if(close(fd_out[0]))
        dprintf(2, "forking error: close fd_out[1]\n");
    free(fd_in);
	free(fd_out);
    return (EXIT_SUCCESS);
}

static void del(void *ptr)
{
    (void)ptr;
    return ;
}

int    process_handler(t_var *var)
{
    t_list  *pid_list;
    t_list  *temp;
    int		status;

    pid_list = NULL;
	printf("return:%i", fork_handler(var, &pid_list, &status));
    temp = pid_list;
	while (pid_list)
	{
		printf("return:%i status:%i\n", waitpid(*((pid_t *)(pid_list->content)), &status, 0), status);
        //WEXITSTATUS(status);
		pid_list = pid_list->next;
	}
    ft_lstclear(&temp, &del);
    return (0);
}
