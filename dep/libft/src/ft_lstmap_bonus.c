/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:15:17 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/25 02:30:26 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_nodel;
	t_list	*ptr;
	void	*content;

	if (!lst)
		return (NULL);
	content = (*f)(lst->content);
	new_nodel = ft_lstnew(content);
	if (!new_nodel)
		return (del(content), NULL);
	ptr = new_nodel;
	lst = lst->next;
	while (lst != NULL)
	{
		content = (*f)(lst->content);
		new_nodel->next = ft_lstnew(content);
		if (!new_nodel->next)
			return (ft_lstclear(&ptr, del), NULL);
		new_nodel = new_nodel->next;
		lst = lst->next;
	}
	return (ptr);
}
