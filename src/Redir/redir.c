/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:03:39 by smagniny          #+#    #+#             */
/*   Updated: 2024/01/22 20:11:25 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

void	base_redir(t_var *var)
{
	if (var->fd_in)
	{
		close(var->fd_in);
		dup2(var->std_in, 0);
		close(var->std_in);
	}
	if (var->fd_out)
	{
		close(var->fd_out);
		dup2(var->std_out, 1);
		close(var->std_out);
	}
}

static	int	here_doc_loop(int fd, char *str, char *lim)
{
	int		i;
	char	buffer;

	while (1)
	{
		write(1, ">", 1);
		i = -1;
		while (read(0, &buffer, 1) && ++i < (int) ft_strlen(lim)
			&& buffer != 10 && lim[i] == buffer)
			str[i] = buffer;
		if (!ft_strncmp(str, lim, (int) ft_strlen(lim)) && buffer == 10)
			return (0);
		write(fd, str, (int)ft_strlen(str));
		ft_bzero(str, i);
		if (buffer != 10 && write(fd, &buffer, 1))
		{
			while (read(0, &buffer, 1) && buffer != 10)
				write(fd, &buffer, 1);
		}
		write(fd, &buffer, 1);
	}
	return (-1);
}

int	here_doc_task(char *lim)
{
	int		fd;
	char	*str;

	fd = open("./here_doc_tmp", O_CREAT | O_RDWR, 0664);
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
	unlink("./here_doc_tmp");
	return (0);
}

int		handle_outfileredirection(t_var *var)
{
	t_node		*tmp;
	t_subnode	*sub_redir_tmp;
	t_subnode	*sub_wheredir_tmp;

	tmp = var->tokens;
	if (!tmp || tmp->redir == NULL || tmp->where_redir == NULL)
		return (0);
	sub_redir_tmp = var->tokens->redir;
	sub_wheredir_tmp = var->tokens->where_redir;
	var->std_out = dup(STDOUT_FILENO);
	while (sub_redir_tmp && sub_wheredir_tmp)
	{
		if (sub_redir_tmp->content == NULL || sub_wheredir_tmp->content == NULL)
			return (0);
		//printf("redir executed: %s\nWhere_file founded: %s\n", sub_redir_tmp->content, sub_wheredir_tmp->content);
		if (ft_strncmp(sub_redir_tmp->content, ">>", 2) == 0)
		{
			var->fd_out = open(sub_wheredir_tmp->content, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (!var->fd_out)
				printf("Minishell: %s: %s\n", \
					strerror(errno),sub_wheredir_tmp->content);
			dup2(var->fd_out, STDOUT_FILENO);
			close(var->fd_out);
		}
		else if (ft_strncmp(sub_redir_tmp->content, ">", 1) == 0 )
		{
			var->fd_out = open(sub_wheredir_tmp->content, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (!var->fd_out)
				printf("Minishell: %s: %s\n", \
					strerror(errno),sub_wheredir_tmp->content);
			dup2(var->fd_out, STDOUT_FILENO);
			close(var->fd_out);
		}
		sub_redir_tmp = sub_redir_tmp->next;
		sub_wheredir_tmp = sub_wheredir_tmp->next;
	}
	return (0);
}

int		handle_infileredirection(t_var *var)
{
	t_subnode	*sub_redir_tmp;
	t_subnode	*sub_wheredir_tmp;

	sub_redir_tmp = var->tokens->redir;
	sub_wheredir_tmp = var->tokens->where_redir;
	if (sub_redir_tmp == NULL || sub_wheredir_tmp == NULL)
		return (0);
	var->std_in = dup(STDIN_FILENO);
	while (sub_redir_tmp && sub_wheredir_tmp)
	{
		if (sub_redir_tmp->content == NULL || sub_wheredir_tmp->content == NULL)
			return (0);
		if (ft_strncmp(sub_redir_tmp->content, "<<", 3) == 0)
		{
			if (here_doc_task(sub_wheredir_tmp->content))
			{
				printf("Minishell: %s\n", strerror(errno));
				return (1);
			}
		}
		else if (ft_strncmp(sub_redir_tmp->content, "<", 2) == 0)
		{
			var->fd_in = open(sub_wheredir_tmp->content, O_RDONLY);
			if (!var->fd_in)
			{
				printf("Minishell: %s: %s\n", \
					strerror(errno),sub_wheredir_tmp->content);
				return (var->fd_out);
			}
			dup2(var->fd_in, STDIN_FILENO);
			close(var->fd_in);
		}
		sub_redir_tmp = sub_redir_tmp->next;
		sub_wheredir_tmp = sub_wheredir_tmp->next;
	}
	return (0);
}
