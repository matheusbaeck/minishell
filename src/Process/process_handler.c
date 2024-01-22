/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:43:44 by math              #+#    #+#             */
/*   Updated: 2024/01/22 20:09:43 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static int task_child(t_var *var, int *fd_in, int *fd_out, int *status) //check for error handle
{
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
    (void)status;
    fprintf(stderr, "cmd: %s\n", var->tokens->token->content);
    fprintf(stderr, "fd_in: %d\n", fd_in[0]);
    fprintf(stderr, "fd_out: %d\n", fd_out[1]);

    dup2(fd_in[0], STDIN_FILENO);
    if (var->tokens->next)
        dup2(fd_out[1], STDOUT_FILENO);
    printf("HEY\n");
    close(fd_in[0]);
    close(fd_in[1]);
    close(fd_out[0]);
    close(fd_out[1]);
    printf("BYE\n");
    if (run_builtin(var))
        ft_exec(var);
    printf("DANGER!!!\n");
    return (127);
}

static int main_task(int **fd_in, int **fd_out, void *next, int *status)
{
    int     *temp;

    close((*fd_in)[0]);
    close((*fd_in)[1]);
    if (!next)
        close((*fd_out)[0]);
    close((*fd_out)[1]);
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
            printf("DANGER\n");
            exit(127);
        }
        else
        {
            ft_lstadd_back(lst, ft_lstnew((void *)&pid));
            printf("parent pid: %d\n", *((pid_t *)(*lst)->content));
            main_task(&fd_in, &fd_out, var->tokens->next, status);
            node_tmp = var->tokens;
            var->tokens = var->tokens->next;
            ft_freenode(&node_tmp);
        }
    }
    free(fd_in);
	free(fd_out);
    return (EXIT_SUCCESS);
}

// pid -> NULL
// ft_lstadd_back(&pid, ft_lstnew(42))  --> node [42][NULL]
// pid == NULL
// pid -> [42][0x1] -> [1337][null]
// 


int    process_handler(t_var *var)
{
    t_list  *pid;
    int		status;

    pid = NULL;
    while (var->tokens)
		fork_handler(var, &pid, &status);
	while (pid)
	{
		waitpid(-1, &status, 0);
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
