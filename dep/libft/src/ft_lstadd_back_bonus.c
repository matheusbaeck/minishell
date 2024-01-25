/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:13:39 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{	
	t_list	*ptr;

	ptr = ft_lstlast(*lst);
	if (ptr != NULL)
		ptr->next = new;
	else
		*lst = new;
}
