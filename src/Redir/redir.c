/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:03:39 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/27 16:30:56 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static int	handle_eof_and_error(int err, char *lim)
{
	if (err <= 0)
	{
		if (ft_strncmp(lim, "eof", 3) == 0)
			return (0);
		else
			return (ms_error("warning", "here-doc terminated by EOF.", 0));
	}
	return (1);
}

int	get_char_hd(int *err, char *buffer, char *lim)
{
	*err = read(0, buffer, 1);
	if (handle_eof_and_error(*err, lim) == 0)
		return (0);
	else
		return (1);
}

static int	here_doc_task(char *lim)
{
	int		fd;
	char	*str;

	signal(SIGINT, ms_heredoc_sig_handler);
	fd = open("./here_doc_tmp", O_CREAT | O_WRONLY, 0664);
	if (fd < 0)
		return (printf("here_doc open file error"), fd);
	str = (char *) ft_calloc((int) ft_strlen(lim) + 1, sizeof(char));
	if (fd == -1 || str == NULL)
	{
		if (str)
			free(str);
		printf("Minishell: %s\n", strerror(errno));
		return (1);
	}
	here_doc_loop(fd, str, lim);
	free(str);
	close(fd);
	fd = open("./here_doc_tmp", O_RDONLY, 0664);
	if (fd < 0)
		exit (errno);
	unlink("./here_doc_tmp");
	return (fd);
}

static int	ft_redir(char *file_name, char *mod)
{
	int	fd;
	int	new_fd;

	fd = 0;
	new_fd = 0;
	if (!ft_strncmp(mod, "<<", 3))
		fd = here_doc_task(file_name);
	else if (!ft_strncmp(mod, "<", 2))
		fd = open(file_name, O_RDONLY);
	else if (ft_strncmp(mod, ">>", 3) == 0)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strncmp(mod, ">", 2))
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Minishell: open");
		exit(1);
	}
	if (!(ft_strncmp(mod, ">>", 3) && ft_strncmp(mod, ">", 2)))
		new_fd = dup2(fd, STDOUT_FILENO);
	else if (!(ft_strncmp(mod, "<<", 3) && ft_strncmp(mod, "<", 2)))
		new_fd = dup2(fd, STDIN_FILENO);
	return (new_fd);
}

int	handle_redirection(t_var *var)
{
	t_subnode	*sub_redir_tmp;
	t_subnode	*sub_wheredir_tmp;
	int			fd;

	sub_redir_tmp = var->tokens->redir;
	sub_wheredir_tmp = var->tokens->where_redir;
	while (sub_redir_tmp && sub_wheredir_tmp)
	{
		fd = ft_redir(sub_wheredir_tmp->content, sub_redir_tmp->content);
		if (fd < 0)
			perror("open");
		sub_redir_tmp = sub_redir_tmp->next;
		sub_wheredir_tmp = sub_wheredir_tmp->next;
	}
	return (fd);
}
