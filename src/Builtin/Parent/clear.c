/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:28:39 by math              #+#    #+#             */
/*   Updated: 2024/02/02 01:35:18 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int clear(t_var *var)
{
    if (var->tokens->params && var->tokens->params->content && *(var->tokens->params->content))
        return (EXIT_FAILURE);
    else
        rl_clear_history();
    return (EXIT_SUCCESS);
}