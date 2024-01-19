/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:54:35 by smagniny          #+#    #+#             */
/*   Updated: 2023/11/30 13:49:30 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
/*FT_PRINTF*/
# include <stdarg.h>
/*GNL*/
# include <limits.h>
// ft_openfd
# include <fcntl.h>

typedef enum t_boolean
{
	False,
	True
}	t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
//openfd
char** copy_2d_array(const char** original);
int		openfd(char *fname);
int		maxx(int a, int b);
int		my_abs(int x);
int		ft_lendb(char **tmp);
void	doublefree(char	**tmp);
int		ft_isdigit_base(char c, int base);
int		ft_atoi_base(const char *str, int base);
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
void	ft_bzero(void *s, size_t n);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, void *src, size_t len);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *dst, const char *str, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinfrees2(char const *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
char	**ssplit(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*FT_PRINTF*/
int		ft_putchar(char c);
int		ft_putnbr(int nb);
int		ft_putstr(char *s);
int		ft_itoalcount(int n);
int		ft_utoa(unsigned long k);
int		ft_putnbrbase(unsigned long int nbr, char *base, int *rtn);
int		ft_printf_char(char c);
int		ft_printf_int(int num);
int		ft_printf_str(char *str);
int		ft_printf_unsigned(unsigned int num);
int		ft_printf(const char *str, ...);

/*GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef FD_INDEX
#  define FD_INDEX FOPEN_MAX
# endif

char	*get_next_line(int fd);
char	*ft_strjoinfrees1(char *oldbuffer, char *tempbuffer);
int		find_occurrence(const char *s, int c);
char	*ft_calloc(size_t count, size_t size);
#endif