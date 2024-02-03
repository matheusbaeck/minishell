/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:11:22 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/03 13:54:54 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

/* static	int	error_identifier(char *identifier)
{
	ft_putstr_fd("Minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (1);
}
 */

//la funcion comprueba que el name de la variable sea alphanum o lowercase. 
static	int	isvalid_namevar(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (1);
	while ((name[i] != '\0') && (name[i] != '='))
	{
		if (!ft_isalnum(name[i]) && (name[i] != '=') && (name[i] != '_'))
			return (printf("Minishell: export: '%s': not a valid identifier\n", \
				name), 1);
		i++;
	}
	return (0);
}

static	int	append_to_env(t_var *var, char **expr, int flag)
{
	char	*name;
	int		exist_already;
	t_env	*tmp_node;

	exist_already = 0; // 0 esque no existe y 1 es que ya existe.
	while ((*expr)[exist_already] != '\0' && (*expr)[exist_already] != '=') //exist_already aqui se usa como iterador pero es solo para ahorrar variables luego se vuelve a poner a 0 y se usa como flag
		exist_already++;
	name = ft_substr((*expr), 0, exist_already);
	exist_already = 0;
	tmp_node = var->envp;
	while (tmp_node)
	{
		if (ft_strncmp(tmp_node->line_env, name, ft_strlen(name)) == 0)
		{
			if (!flag)
			{
				if (tmp_node->line_env)
					free(tmp_node->line_env);
				tmp_node->line_env = ft_strjoinfreee(name, \
					ft_strjoin("=", ft_strchr(*expr, '=') + 1));
				return (0);
			}
			exist_already = 1;
			if (flag)
				free(name);
		}
		tmp_node = tmp_node->next;
	}
	if (exist_already)
		return (0);
    // Allocate new node line content for env.
	ft_addback_node_env(&var->envp, new_node_env((*expr), flag));
	if (exist_already == 0)
		free(name);
	return (0);
}

static	void	print_export_values(char	**envp)
{
	int		line;
	int		col;
	char	*res;
	char	*name;
	char	*val;


	line = 0;
	col = 0;
	res = NULL;
	val = NULL;
	while (envp[line])
	{
		while (envp[line][col] != '\0' && envp[line][col] != '=')
			col++;
		name = ft_substr(envp[line], 0, col);
		val = ft_substr(envp[line], col + 1, ft_strlen(envp[line]) - col + 1);
		if (!val || !*val)
		{
			free(val);
			res = name;
		}
		else
			res = ft_strjoinfreee(name, ft_strjoinfrees2("=", ft_strjoinfrees2("\"\0", ft_strjoinfrees1(val, "\"\0"))));
		printf("%s\n", res);
		free(res);
		line++;
		col = 0;
	}
}

static	int	show_values_alpha(t_var *var)
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

// /* 
// export [name[=value]]
// */
int	export(t_var *var)
{
	t_subnode	*tmp;

	tmp = var->tokens->params;
	if (var->tokens->next)
		return (EXIT_SUCCESS);
	if (no_flags_supported(var->tokens->params))
		return (SYNTAX_ERROR);
	if (!tmp && !var->tokens->redir && !var->tokens->where_redir)
		return (show_values_alpha(var));  // ejecutar export sin args, mostrar env en orden alphabetico
	while (tmp) //iterar en los params del nodo export.
	{
		if (isvalid_namevar(tmp->content))// verificar que sea alphanum o '_'
			return (1);
		if (ft_strchr(tmp->content, '='))
			append_to_env(var, &tmp->content, 0); // anade la var_name con su valor.
		else
			append_to_env(var, &tmp->content, 1); // anade la var_name sin valor
		tmp = tmp->next;
	}
	return (0);
}

