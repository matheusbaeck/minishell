/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:43:44 by math              #+#    #+#             */
/*   Updated: 2024/01/22 17:22:09 by math             ###   ########.fr       */
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

static int task_child(t_var *var, int *fd_in, int *fd_out, int *status) //check for error handle
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
    if (close_pipe(fd_in, status))
        return (CLOSE_FAIL);
    if (close_pipe(fd_out, status))
        return (CLOSE_FAIL);
    if (run_builtin(var))
        ft_exec(var);
    printf("DANGER!!!\n");
    return (127);
}

static int main_task(int **fd_in, int **fd_out, int *status)
{
    int     *temp;

    if (close_pipe(*fd_in, status))
        return (CLOSE_FAIL);
    if (close_pipe_write(*fd_out, status))
        return (CLOSE_FAIL);
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

// static void print_lst(t_list **lst)
// {
//     t_list *current;
//     int node_count;

//     printf("PRINTING LIST\n");
//     if (!lst || !(*lst))
//         return ;
//     current = (*lst);
//     node_count = 1;
//     while (current)
//     {
//         printf("Node %d:%p, Content:%p(", node_count, (void *)current, current->content);

//         if (current->content)
//             printf("%d)", *((pid_t *)current->content));
//         else
//             printf("(null)");

//         if (current->next)
//             printf(", next:%p", current->next);
//         else
//             printf(", next:(null)");

//         printf("\n");

//         current = current->next;
//         node_count++;
//     }
// }

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
            // if (!task_child(var, fd_in, fd_out, status))
            //     return (EXIT_FAILURE);
        }
        else
        {
            // printf("pointers lst:%p *lst:%p (*lst)->content:%p (*lst)->next:%p\n", lst, *lst, (*lst)->content, (*lst)->next);
            if (!(*lst))
            {
                *lst = ft_lstnew((void *)&pid);
            }
            else
                ft_lstadd_back(lst, ft_lstnew((void *)&pid));
            main_task(&fd_in, &fd_out, status);
            // if (!main_task(var, &fd_in, &fd_out, status))
            //     return (EXIT_FAILURE);
            node_tmp = var->tokens;
            var->tokens = var->tokens->next;
            ft_freenode(&node_tmp);
            //print_lst(lst);
            if ((*lst)->next)
                exit (0);
        }
    }
    free(fd_in);
	free(fd_out);
    return (EXIT_SUCCESS);
}

int    process_handler(t_var *var)
{
    t_list  *pid;
    int		status;

    //pid = (t_list *)malloc(sizeof(t_list));
    while (var->tokens)
		fork_handler(var, &pid, &status);
	while (pid)
	{
		waitpid(*((pid_t *)pid->content), &status, 0);
        //WEXITSTATUS(status);
		pid = pid->next;
	}
    ft_lstclear(&pid, NULL); //verify that function acept NULL as param
    free(pid);
    // free all dat
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
