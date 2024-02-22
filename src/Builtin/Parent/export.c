/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:11:22 by mohafnh           #+#    #+#             */
/*   Updated: 2024/02/22 13:51:30 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header.h"

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
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("` not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	if (ft_atoi(name) || *name == '=' || *name == '\0')
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("` not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	update_var(int flag, t_env **line_env, char *name, char *val)
{
	if (!flag)
	{
		if (!val)
			return (-1);
		if ((*line_env)->line_env)
			free((*line_env)->line_env);
		(*line_env)->line_env = ft_strjoinfreee(name, val);
		(*line_env)->exported = 0;
		return (1);
	}
	else
		return (0);
}

static char	*retrieve_name(char *expr)
{
	int	i;

	i = 0;
	while (expr[i] != '\0' && expr[i] != '=')
		i++;
	return (ft_substr(expr, 0, i));
}

static	int	append_to_env(t_var *var, char **expr, int flag)
{
	char	*name;
	char	*val;
	int		exist_already;
	t_env	*tmp_node;

	name = retrieve_name((*expr));
	val = retrieve_value(*expr);
	exist_already = 0;
	tmp_node = var->envp;
	while (tmp_node)
	{
		if (ft_strncmp(tmp_node->line_env, name, ft_strlen(name)) == 0)
			exist_already = update_var(flag, &tmp_node, name, val);
		tmp_node = tmp_node->next;
	}
	if (exist_already)
		return (0);
	else
	{
		free(val);
		free(name);
	}
	ft_addback_node_env(&var->envp, new_node_env((*expr), flag));
	return (0);
}

int	export(t_var *var)
{
	t_subnode	*tmp;

	tmp = var->tokens->params;
	if (var->tokens->next)
		return (EXIT_SUCCESS);
	if (no_flags_supported(var->tokens->params))
		return (SYNTAX_ERROR);
	if (!tmp && !var->tokens->redir && !var->tokens->where_redir)
		return (show_values_alpha(var));
	while (tmp)
	{
		if (isvalid_namevar(tmp->content))
		{
			g_status = 2;
			return (1);
		}
		if (ft_strchr(tmp->content, '='))
			append_to_env(var, &tmp->content, 0);
		else
			append_to_env(var, &tmp->content, 1);
		tmp = tmp->next;
	}
	return (0);
}
