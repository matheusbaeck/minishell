/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:56:36 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/19 15:03:21 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//(===||[:::::::::::::::>
static	void	get_dir(t_env *envp, char **pwd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = expand(envp, "HOME");
	while (tmp && tmp[i] && (*pwd)[i] && (*pwd)[i] == tmp[i])
		i++;
	free(tmp);
	tmp = ft_strdup(&(*pwd)[i]);
	free((*pwd));
	(*pwd) = tmp;
}

static	void	create_prompt(t_env *envp, char **string)
{
	char	*cur_path;
	char	*str;

	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
		perror("Error al obtener el directorio actual");
	get_dir(envp, &cur_path);
	str = ft_strjoinfrees1(expand(envp, "LOGNAME"), "@");
	str = ft_strjoinfreee(str, expand(envp, "NAME"));
	str = ft_strjoinfrees1(str, ":");
	str = ft_strjoinfreee(str, cur_path);
	(*string) = ft_strjoinfrees1(str, "$ ");
}

char	*get_inputline(t_var *var)
{
	char			*str;
	char			*prompt;

	create_prompt(var->envp, &prompt);
	str = readline(prompt);
	free(prompt);
	if (!str || str == NULL)
	{
		ft_printf("exit\n");
		var->inputline = NULL;
		return (NULL);
	}
	var->inputline = ft_strdup(str);
	free(str);
	add_history(var->inputline);
	return (var->inputline);
}

void	updt_shlvl(t_env	**envp)
{
	t_env	*nodetmp;
	int		shlvl;

	shlvl = 0;
	nodetmp = *envp;
	if (!envp)
		return ;
	while (nodetmp)
	{
		if (ft_strncmp(nodetmp->line_env, "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(nodetmp->line_env + 6) + 1;
			free(nodetmp->line_env);
			nodetmp->line_env = ft_strjoinfrees2("SHLVL=", ft_itoa(shlvl));
		}
		nodetmp = nodetmp->next;
	}
}
