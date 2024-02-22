/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:56:36 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/22 14:05:17 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*get_inputline(t_var *var)
{
	char			*str;
	char			*prompt;

	str = readline("Minishell$ ");
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
