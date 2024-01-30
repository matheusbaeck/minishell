/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:56:45 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/30 20:06:23 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

void	sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}

void	sigint_childhandler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
	exit(130);
}

void	interactive_mode_signals(void (*func)(int sig))
{
	struct	sigaction   act;

    act.sa_flags = SA_RESTART;
    sigemptyset(&act.sa_mask);
	act.sa_handler = func;
    if (sigaction(SIGINT, &act, NULL) == -1)
		perror(strerror(errno));
}

int	ms_get_capabilities(void)
{
	struct termios	attr;

	if (!isatty(0))
	{
		return (1);
	}
	if (tcgetattr(0, &attr) == -1)
	{
		return (1);
	}
	attr.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, TCSANOW, &attr) == -1)
	{
		return (1);
	}
	return (0);
}