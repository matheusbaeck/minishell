/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:28:39 by math              #+#    #+#             */
/*   Updated: 2024/02/19 12:37:04 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	clear(t_var	*var)
{
	if (var->tokens->params && var->tokens->params->content
		&& *(var->tokens->params->content))
		return (EXIT_FAILURE);
	else
	{
		clear_history();
		write(STDOUT_FILENO, "\033[H\033[2J", 7);
	}
	return (EXIT_SUCCESS);
}
