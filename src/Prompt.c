
#include "../header.h"

// (===||[:::::::::::::::>

static	void	get_dir(t_env *envp, char **pwd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = expand(envp, "HOME");
	while (tmp[i] && (*pwd)[i] && (*pwd)[i] == tmp[i])
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

static	void	sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}

void	interactive_mode_signals(void)
{
	struct	sigaction   act;

    act.sa_flags = SA_RESTART;
    sigemptyset(&act.sa_mask);
	act.sa_handler = &sigint_handler;
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