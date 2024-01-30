#include "../../header.h"

// static t_node	*ft_lstnew_node_wcontent(char *content)
// {
// 	t_node	*ptr;

// 	ptr = (t_node *)malloc(sizeof(t_node));
// 	if (!(ptr))
// 		return (NULL);
//     if (content == NULL)
//         ptr->token = NULL;
//     else
//         ptr->token = ft_lstnew_subnode(content);
// 	ptr->flags = NULL;
// 	ptr->params = NULL;
// 	ptr->redir = NULL;
// 	ptr->where_redir = NULL;
// 	ptr->next = NULL;
// 	return (ptr);
// }

static int is_operator(char *line)
{
    return (line[0] == '|' && line[1] == '|') || (line[0] == '&' && line[1] == '&');
}

static int should_cut(char *line)
{
    if (line[0] == '(' || is_operator(line))
        return (1);
    return (0);
}

// static int get_closing_parenthesis(char *line)
// {
//     int count;
//     int i;

//     count = 1;
//     i = -1;
//     while (count > 0 && line[++i])
//     {
//         if (line[i] == '(')
//             count++;
//         else if (line[i] == ')')
//             count--;
//     }
//     if (count == 0)
//         return (i);
//     return (0);
// }

static char *str_cut(char **s1, int start, int skip)
{
    char    *s2;
    char    *temp;

    printf("0 -> %i && %i -> %i\n%s\n", start, start + skip, ft_strlen(&(*s1)[start + skip]), *s1);
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

void get_treeline(t_var *var)
{
    int     i;
    t_node  *current;

    while (current)
    {
        i = -1;
        while ((current->token->content)[++i])
        {
            if (should_cut(&((current->token->content)[i])))
            {
                if ((current->token->content)[i] == '(' && i > 0)
                {
                    /* get_closing_parenthesis*/
                    ft_lstadd_back(var->tokens, ft_lstnew((void *)str_cut((char **)(&current->token->content), i, 1)));
                    printf("%s %s\n", current->token->content, current->next->token->content);
                    //get_treeline(&current->next, &get_closing_parenthesis);
                    break;
                }
                else
                {
                    ft_lstadd_back(var->tokens, ft_lstnew((void *)str_cut((char **)(&(current->token->content)), i, 2)));
                    break;
                }
            }
        }
        current = current->next;
    }
}

// static int  is_parenthesis(t_node *node)
// {
//     if (node->tokens == NULL)
//         return (node->tokens->params)
//     return (0);
// }

int call_print_tree(t_var *var)
{
    t_node *current;

    get_treeline(&var->tokens);
    current = var->tokens;
    while (current)
    {
        printf("%p:%s\n", current, ((char *)current->token->content));
        current = current->next;
    }
    return 0;
}