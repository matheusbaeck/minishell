/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <smagniny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:35:31 by smagniny          #+#    #+#             */
/*   Updated: 2024/02/21 17:01:06 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "dep/libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>

# include <stddef.h> // Incluye la librería para definir NULL
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# define SINGLEQ '\''
# define DOUBLEQ '\"'

//bash originals
//custom
enum	e_bash_errors
{
	SYNTAX_ERROR=2,
	COMMAND_NOT_FOUND=127,
	PERMISSION_DENIED=126,
	FILE_NOT_FOUND=1,
	DISK_FULL=1,
	FORK_ERROR=128,
	PIPE_ERROR=129,
	CLOSE_ERROR=130,
	MALLOC_ERROR=131,
	QUOTE_ERROR= SYNTAX_ERROR
};

enum	e_builtin_return
{
	IS_BUILTIN = 1,
	IS_NOT_BUILTIN = 0,
};

extern int	g_status;

typedef struct s_subnode
{
	char				*content;
	struct s_subnode	*next;
}	t_subnode;

typedef struct s_node
{
	t_subnode			*token;
	//t_subnode			*flags;
	t_subnode			*params;
	t_subnode			*redir;
	t_subnode			*where_redir;
	struct s_node		*next;
}	t_node;

typedef struct s_node_env
{
	char				*line_env;
	int					exported;
	struct s_node_env	*next;
}	t_env;

typedef struct s_var
{
	size_t		std_in;
	size_t		std_out;
	size_t		fd_in;
	size_t		fd_out;
	t_env		*envp;
	char		*inputline;
	int			len_inputline;
	int			nb_node;
	t_node		*tokens;
}	t_var;

//			###### lexer/Parser ######
int			lexer(t_var *var);
int			gnt_startpoint(t_var *var, int start);
char		*check_word_rec(t_var *var, int *start, int *i, char *token_string);
int			is_space_or_eof(int c);
int			isingle_operator(char *line, int i);
int			isdouble_operator(char *line, int i);
int			issinglequote(int c);
int			isdoublequote(int c);
int			is_operator_grouping(char *line);
int			is_operator_semicolon(char *line);
char		*ft_strjoinfreee(char *s1, char *s2);
char		*getstr_dbq(t_var *var, int *i, int *start);
char		*getstr_sq(t_var *var, int *i, int *start);
char		*get_word(t_var *var, int *i, int *start);
// <---------------------------------->
// 			###### get input ######
char		*get_inputline(t_var *var);
void		rl_replace_line(const char *text, int clear_undo);
// <---------------------------------->
// 			###### expansion ######
void		expansor(t_var *var, char **string, int doublequoted);
char		*expand(t_env *env, char *dollar_str);
void		*my_realloc(void *ptr, size_t originalLength, size_t newLength);
void		are_any_expansion(char **res, char **string, int ref);
void		start_values_normi(int *i, int *ref, char **res);
// <---------------------------------->
// 			######list node functions ######
void		ft_lstdelone_subnode(t_subnode *lst);
void		ft_lstclear_node(t_node **lst);
void		ft_lstdelone_node(t_node *node);
t_node		*ft_lstdelone_node_getnext(t_node *node);
void		ft_freenode(t_node **node);
t_node		*ft_lstnew_node(void);
t_node		*ft_lstlast_node(t_node *lst);
void		ft_lstadd_back_node(t_node **lst, t_node *new);
void		printnodes(t_node **node);
// <---------------------------------->
// 			######list subnode functions ######
void		ft_lstclear_subnode(t_subnode **lst);
t_subnode	*ft_lstnew_subnode(char *content);
t_subnode	*ft_lstlast_subnode(t_subnode *lst);
void		ft_lstadd_back_subnode(t_subnode **lst, t_subnode *new);
// <----------------------------------->
//			###### list environment functions ######
void		ft_expansor(t_var *var);
void		cpy_env(t_env **ptr, const char **envp);
void		ft_freeenv(t_env **lst);
t_env		*new_node_env(const char *line_env, int exported);
void		ft_addback_node_env(t_env **lst, t_env *new);
char		**envlist_to_array(t_env *envlist);
char		**set_params_to_array(t_node *node);
void		updt_shlvl(t_env **envp);
int			show_values_alpha(t_var *var);
// <----------------------------------->
//			###### redir funcs ######
int			handle_redirection(t_var *var);
// <---------------------------------->
//			###### External command execution ######
int			ft_exec(t_var *var);
int			process_handler(t_var *var);
int			close_pipe_read(int *fd);
int			close_pipe_write(int *fd);
int			close_pipe(int *fd);
int			destroy_pipe(int *fd);
int			is_cut_point(char *line);
int			pipe_split(t_list **node, int (*fptr)(char *));
// <---------------------------------->
//			###### Builtins ######
int			no_flags_supported(t_subnode *subnode_param);
int			run_builtin_parent(t_var *var, int *last_status);
int			exit_minishell(t_var *var);
int			unset(t_var *var);
int			export(t_var *var);
char		*retrieve_value(char *expr);
int			cd(t_node *tokens);
int			clear(t_var *var);
int			run_builtin_child(t_var *var, int *last_status);
int			echo(t_node *tokens);
int			pwd(t_var	*var);
int			env(t_var *var);
// <---------------------------------->
//			###### Signals ######
int			ms_signal(void);
void		ms_signal_handler(int sig);
void		ms_heredoc_sig_handler(int sig);
int			ms_get_capabilities(void);

int			ms_error(char *type_err, char *err_context, int code_err);
#endif
