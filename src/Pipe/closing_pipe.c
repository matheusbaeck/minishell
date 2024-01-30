/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:21:58 by math              #+#    #+#             */
/*   Updated: 2024/01/30 10:56:51 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int close_pipe_read(int *fd)
{
    int err;

    if (!fd || fd[0] < 2)
        return (EXIT_SUCCESS);
    err = close(fd[0]);
    if (err)
        return (printf("close pipe[0] fail %i\n", err), CLOSE_ERROR);
    return (EXIT_SUCCESS);
}

int close_pipe_write(int *fd)
{
    int err;

    if (!fd || fd[1] < 2)
        return (EXIT_SUCCESS);
    err = close(fd[1]);
    if (err)
        return (printf("close pipe[1] fail %i\n", err), CLOSE_ERROR);
    return (EXIT_SUCCESS);
}

int close_pipe(int *fd)
{
    if (close_pipe_write(fd))
        return (CLOSE_ERROR);
    if (close_pipe_read(fd))
        return (CLOSE_ERROR);
    return (0);
}

int destroy_pipe(int *fd)
{
    if (close_pipe(fd))
        return (CLOSE_ERROR);
    free(fd);
    return (0);
}
