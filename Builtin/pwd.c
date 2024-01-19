/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 03:41:02 by mohafnh           #+#    #+#             */
/*   Updated: 2024/01/17 19:09:54 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	pwd(t_var	*var)
{
	char	*path;

	if (var->tokens->flags != NULL)
	{
		printf("Minishell: pwd: no options can be handled.\n");
		return (1);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("Error al obtener el directorio actual");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
