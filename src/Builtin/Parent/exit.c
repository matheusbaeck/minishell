/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:44:45 by math              #+#    #+#             */
/*   Updated: 2024/01/25 02:37:52 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int exit_minishell(t_var *var)
{
    int exit_val;

    if (var->tokens->flags == NULL
        && var->tokens->redir == NULL)
    {
        if (var->tokens->params == NULL)
            exit_val = 0;
        else
            exit_val = *((int *)(var->tokens->params->content));
        ft_lstclear_node(&var->tokens);
        free(var->tokens);
        ft_freeenv(&var->envp);
        exit (exit_val);
    }
    return (0);
}