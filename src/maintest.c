/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:43:49 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/22 19:23:43 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/header.h"

static	void	init_ms(t_var *var, const char	**envp)
{
	var->envp = NULL;
	var->inputline = NULL;
	cpy_env(&var->envp, envp);
}

static void	init_values(t_var *var)
{
	var->fd_in = 0;
	var->fd_out = 0;
    var->tokens = NULL;
    var->nb_node = 0;
	var->exit_status = 0;
}

static void printNode(t_node *node)
{
    if (node == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("Token: %s\n", node->token->content);

    // Print flags
    printf("Flags: ");
    t_subnode *flags = node->flags;
    while (flags != NULL)
    {
        printf("%s ", flags->content);
        flags = flags->next;
    }
    printf("\n");

    // Print params
    printf("Params: ");
    t_subnode *params = node->params;
    while (params != NULL)
    {
        printf("%s ", params->content);
        params = params->next;
    }
    printf("\n");

    // Print redir
    printf("Redir: ");
    t_subnode *redir = node->redir;
    while (redir != NULL)
    {
        printf("%s ", redir->content);
        redir = redir->next;
    }
    printf("\n");

    // Print where_redir
    printf("Where Redir: ");
    t_subnode *where_redir = node->where_redir;
    while (where_redir != NULL)
    {
        printf("%s ", where_redir->content);
        where_redir = where_redir->next;
    }
    printf("\n");

}

void    printNodes(t_node **node)
{
    int i;
    t_node *tmp;

    tmp = *node;
    i = 0;
    while (tmp)
    {
        ++i;
        printf("NODE -> %i\n", i);
        printNode(tmp);
        tmp = tmp->next;
    }
    printf("EXECUTION:\n");
}

int	main(int argc, char **argv, const char **envp)
{
	t_var	var;

	init_ms(&var, envp);
	while (get_inputline(&var))
	{
		init_values(&var);
		lexer(&var);
        if (argc > 1 && !ft_strncmp(argv[1], "print", 6))
        {
            printNodes(&var.tokens);
            exit (0);
        }
        process_handler(&var);
		base_redir(&var);
		free(var.tokens);
	}
	ft_freeenv(&var.envp);
	return (0);
}
