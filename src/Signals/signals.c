/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:56:45 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/18 22:55:38 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_status;

void	signal_handler(int sig)
{
	if (sig != SIGINT)
	{
		rl_redisplay();
		return ;
	}
	if (waitpid(-1, &g_status, 0) > 0)
	{
		g_status = 130;
		write(1, "\n", 1);
		return ;
	}
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ms_heredoc_sig_handler(int sig)
{
	(void) sig;
	write(1, "\n^C", 3);
	unlink("./here_doc_tmp");
	exit(1);
}

int	ms_signal(void)
{
	size_t				i;
	int					err;
	struct sigaction	sa;
	const int			sigs[3] = {SIGINT, SIGTSTP, SIGQUIT};

	i = 0;
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	while (i < 3)
	{
		if (sigs[i] == SIGQUIT)
			sa.sa_handler = SIG_IGN;
		err = sigaction(sigs[i], &sa, NULL);
		if (err == -1)
		{
			ft_printf("Minishell: %s\n", strerror(errno));
			return (1);
		}
		i += 1;
	}
	return (0);
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
