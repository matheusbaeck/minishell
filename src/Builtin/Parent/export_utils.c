/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:01:26 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/21 17:00:25 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

static	void	print_env_line(char *name, char	*val, int *line, int *col)
{
	char	*res;

	res = NULL;
	if (!val || !*val)
	{
		free(val);
		res = name;
	}
	else
	{
		res = ft_strjoinfrees2("\"", ft_strjoinfrees1(val, "\""));
		res = ft_strjoinfreee(name, ft_strjoinfrees2("=", res));
	}
	printf("%s\n", res);
	free(res);
	(*line)++;
	*col = 0;
}

static	void	print_export_values(char	**envp)
{
	int		line;
	int		col;
	char	*name;
	char	*val;

	line = 0;
	col = 0;
	val = NULL;
	while (envp[line])
	{
		while (envp[line][col] != '\0' && envp[line][col] != '=')
			col++;
		name = ft_substr(envp[line], 0, col);
		val = ft_substr(envp[line], col + 1, ft_strlen(envp[line]) - col + 1);
		print_env_line(name, val, &line, &col);
	}
}

int	show_values_alpha(t_var *var)
{
	char	**envp;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	envp = envlist_to_array(var->envp);
	while (envp[i])
	{
		j = 0;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) < 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export_values(envp);
	doublefree(envp);
	return (0);
}

char	*retrieve_value(char *expr)
{
	int	i;
	int	len;

	len = ft_strlen(expr);
	i = 0;
	while (expr[i] != '\0' && expr[i] != '=')
		i++;
	if (i >= len)
		return (NULL);
	else
		return (ft_substr(expr, i, ft_strlen(expr)));
}
