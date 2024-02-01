
#include "../header.h"

// (===||[:::::::::::::::>

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
	char			*cur_path;

	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
		perror("Error al obtener el directorio actual");
    get_dir(envp, &cur_path);
/*     ft_strjoinfrees2("\033[1;32m", expand(var->envp, "LOGNAME"))  
    ft_strjoinfrees1(ft_strjoinfrees2("\033[1;32m", expand(var->envp, "LOGNAME")), "@")
    ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfrees2("\033[1;32m", expand(var->envp, "LOGNAME")), "@"), expand(var->envp, "NAME"));
    ft_strjoinfrees1(ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfrees2("\033[1;32m", expand(var->envp, "LOGNAME")), "@"), expand(var->envp, "NAME")), "\033[0m:\033[1;34m~");
    ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfrees2("\033[1;32m", expand(var->envp, "LOGNAME")), "@"), expand(var->envp, "NAME")), "\033[0m:\033[1;34m~"), cur_path);
    ft_strjoinfrees1(ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfrees2("\033[1;32m", expand(var->envp, "LOGNAME")), "@"), expand(var->envp, "NAME")), "\033[0m:\033[1;34m~"), cur_path), "\033[0m$") */
	(*string) = ft_strjoinfrees1(ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfreee(ft_strjoinfrees1(ft_strjoinfrees2("\033[1;32m", expand(envp, "LOGNAME")), "@"), expand(envp, "NAME")), "\033[0m:\033[1;34m~"), cur_path), "\033[0m$>");
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
