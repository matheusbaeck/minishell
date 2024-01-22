/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:21:58 by math              #+#    #+#             */
/*   Updated: 2024/01/20 19:55:30 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int close_pipe_read(int *fd, int *status)
{
    *status = close(fd[0]);
    if (*status)
        return (CLOSE_FAIL);
    return (0);
}

int close_pipe_write(int *fd, int *status)
{
    *status = close(fd[1]);
    if (*status)
        return (CLOSE_FAIL);
    return (0);
}

int close_pipe(int *fd, int *status)
{
    if (close_pipe_write(fd, status))
        return (CLOSE_FAIL);
    if (close_pipe_read(fd, status))
        return (CLOSE_FAIL);
    return (0);
}

int destroy_pipe(int *fd, int *status)
{
    if (close_pipe(fd, status))
        return (CLOSE_FAIL);
    free(fd);
    return (0);
}
