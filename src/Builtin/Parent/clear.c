/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:28:39 by math              #+#    #+#             */
/*   Updated: 2024/02/18 13:12:58 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

int	clear(t_var	*var)
{
	if (var->tokens->params && var->tokens->params->content
		&& *(var->tokens->params->content))
		return (EXIT_FAILURE);
	else
		rl_clear_history();
	return (EXIT_SUCCESS);
}
