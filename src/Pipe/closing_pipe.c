/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:21:58 by math              #+#    #+#             */
/*   Updated: 2024/02/07 23:42:30 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	close_pipe_read(int	*fd)
{
	int		err;

	if (!fd || fd[0] < 2)
		return (EXIT_SUCCESS);
	err = close(fd[0]);
	if (err)
		return (printf("close pipe[0] fail %i\n", err), CLOSE_ERROR);
	return (EXIT_SUCCESS);
}

int	close_pipe_write(int *fd)
{
	int		err;

	if (!fd || fd[1] < 2)
		return (EXIT_SUCCESS);
	err = close(fd[1]);
	if (err)
		return (printf("close pipe[1] fail %i\n", err), CLOSE_ERROR);
	return (EXIT_SUCCESS);
}

int	close_pipe(int *fd)
{
	if (close_pipe_write(fd))
		return (CLOSE_ERROR);
	if (close_pipe_read(fd))
		return (CLOSE_ERROR);
	return (0);
}

int	destroy_pipe(int *fd)
{
	if (close_pipe(fd))
		return (CLOSE_ERROR);
	free(fd);
	return (0);
}
