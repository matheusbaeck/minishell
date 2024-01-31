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

void	sigint_handler(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;
	(void)sig;
    if (info->si_pid != 0) {
        // Signal was sent by a process with the same real UID
		write(1,"\n", 1);
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    } else {
        // Signal was sent by a child process
        //exit(130);
    }
}

void	interactive_mode_signals(void)
{
	struct	sigaction   act;

    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
	act.sa_sigaction = sigint_handler;
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