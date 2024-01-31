#include "../../header.h"

static int is_operator_or(char *line)
{
    if (line[0] == '|' && line[1] == '|')
        return (2);
    return (0);
}

static int is_operator_and(char *line)
{
    if (line[0] == '&' && line[1] == '&')
        return (2);
    return (0);
}

static int is_operator_pipe(char *line)
{
    if (line[0] == '|' && !is_operator_or(line))
        return (1);
    return (0);
}

static int is_operator_bkgexec(char *line)
{
    if (line[0] == '&' && !is_operator_and(line))
        return (1);
    return (0);
}

static int is_operator_semicolon(char *line)
{
    if (line[0] == ';')
        return (1);
    return (line[0] == ';');
}

static int is_operator_grouping(char *line)
{
    if (line[0] == '(' || line[0] == ')' || line[0] == '{' || line[0] == '}')
        return (1);
    return (0);
}

int is_cut_point(char *line)
{
    if (is_operator_and(line) || is_operator_or(line) ||
        is_operator_bkgexec(line) || is_operator_semicolon(line) ||
        is_operator_semicolon(line) || is_operator_grouping(line))
        return (-1);
    return (is_operator_pipe(line));
}


static char *str_cut(char **s1, int start, int skip)
{
    char    *s2;
    char    *temp;

    if (start < 0 || start + skip >= ft_strlen(*s1))
        return (NULL);
    s2 = malloc((ft_strlen(&(*s1)[start + skip]) + 1) * sizeof(char));
    if (!s2)
        return (NULL);
    ft_strlcpy(s2, &(*s1)[start + skip], ft_strlen(&(*s1)[start + skip]) + 1);
    temp = *s1;
    *s1 = malloc((start + 1) * sizeof(char));
    if (!(*s1))
        return (NULL);
    ft_strlcpy(*s1, temp, start + 1);
    free(temp);
    return (s2);
}

int pipe_split(t_list **node, int (*fptr)(char *))
{
    t_list  *current = *node;
    int     i;
    int     ret;

    while (current)
    {
        i = -1;
        while (((char *)current->content)[++i])
        {
            ret = fptr(&(((char *)current->content)[i]));
            if (ret > 0)
            {
                ft_lstadd_back(node, ft_lstnew((void *)str_cut((char **)(&current->content), i, 1)));
                if (current->next->content == NULL)
                    return (free(current->next), current->next = NULL, -1);
                break;
            }
            else if(ret < 0)
                return (-1);
        }
        current = current->next;
    }
    return (0);
}

// #include "../../header.h"

// static t_node	*ft_lstnew_node_wcontent(char *content)
// {
// 	t_node	*ptr;

// 	ptr = (t_node *)malloc(sizeof(t_node));
// 	if (!(ptr))
// 		return (NULL);
//     ptr->token = ft_lstnew_subnode(content);
// 	ptr->flags = NULL;
// 	ptr->params = NULL;
// 	ptr->redir = NULL;
// 	ptr->where_redir = NULL;
// 	ptr->next = NULL;
// 	return (ptr);
// }

// static int is_operator(char *line)
// {
//     return (line[0] == '|' && line[1] == '|') || (line[0] == '&' && line[1] == '&');
// }

// static int should_cut(char *line)
// {
//     if (line[0] == '(' || is_operator(line))
//         return (1);
//     return (0);
// }

// // static int get_closing_parenthesis(char *line)
// // {
// //     int count;
// //     int i;

// //     count = 1;
// //     i = -1;
// //     while (count > 0 && line[++i])
// //     {
// //         if (line[i] == '(')
// //             count++;
// //         else if (line[i] == ')')
// //             count--;
// //     }
// //     if (count == 0)
// //         return (i);
// //     return (0);
// // }

// static char *str_cut(char **s1, int start, int skip)
// {
//     char    *s2;
//     char    *temp;

//     printf("0 -> %i && %i -> %i\n%s\n", start, start + skip, ft_strlen(&(*s1)[start + skip]), *s1);
//     if (start < 0 || start + skip >= ft_strlen(*s1))
//         return (NULL);
//     s2 = malloc((ft_strlen(&(*s1)[start + skip]) + 1) * sizeof(char));
//     if (!s2)
//         return (NULL);
//     ft_strlcpy(s2, &(*s1)[start + skip], ft_strlen(&(*s1)[start + skip]) + 1);
//     temp = *s1;
//     *s1 = malloc((start + 1) * sizeof(char));
//     if (!(*s1))
//         return (NULL);
//     ft_strlcpy(*s1, temp, start + 1);
//     free(temp);
//     return (s2);
// }

// void get_treeline(t_var *var)
// {
//     int     i;
//     t_node  *current;

//     while (current)
//     {
//         i = -1;
//         while ((current->token->content)[++i])
//         {
//             if (should_cut(&((current->token->content)[i])))
//             {
//                 if ((current->token->content)[i] == '(' && i > 0)
//                 {
//                     /* get_closing_parenthesis*/
//                     ft_lstadd_back_node(&var->tokens, ft_lstnew_node_wcontent((void *)str_cut((char **)(&current->token->content), i, 1)));
//                     printf("%s %s\n", current->token->content, current->next->token->content);
//                     //get_treeline(&current->next, &get_closing_parenthesis);
//                     break;
//                 }
//                 else
//                 {
//                     ft_lstadd_back_node(&var->tokens, ft_lstnew_node_wcontent((void *)str_cut((char **)(&(current->token->content)), i, 2)));
//                     break;
//                 }
//             }
//         }
//         current = current->next;
//     }
// }

// // static int  is_parenthesis(t_node *node)
// // {
// //     if (node->tokens == NULL)
// //         return (node->tokens->params)
// //     return (0);
// // }

// int call_print_tree(t_var *var)
// {
//     t_node *current;

//     get_treeline(var);
//     current = var->tokens;
//     while (current)
//     {
//         printf("%p:%s\n", current, ((char *)current->token->content));
//         current = current->next;
//     }
//     return 0;
// }