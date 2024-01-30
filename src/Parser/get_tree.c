#include "../../header.h"

static int is_operator(char *line)
{
    return (line[0] == '|' && line[1] == '|') || (line[0] == '&' && line[1] == '&');
}

static int should_cut(char *line, int *i)
{
    if (line[0] == '(')
        *i+=1;
    else if (is_operator(line))
        *i+=2;
    else
        return (0);
    return (1);
}

int get_closing_parenthesis(char *line)
{
    int count;
    int i;

    count = 1;
    i = -1;
    while (count > 0 && line[++i])
    {
        if (line[i] == '(')
            count++;
        else if (line[i] == ')')
            count--;
    }
    if (count == 0)
        return (i);
    return (0);
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

void get_treeline(t_list **node)
{
    t_list  *current = *node;
    int     i;

    while (current)
    {
        i = -1;
        while (((char *)current->content)[++i])
        {
            printf("%i:%c\n",i , ((char *)current->content)[i]);
            if (should_cut(&(((char *)current->content)[i]), &i))
            {
                printf("if statment\n");
                printf("%i:%c\n",i , ((char *)current->content)[i]);
                if (((char *)current->content)[i] == '(' && i > 0)
                {
                    /* get_closing_parenthesis*/
                    ft_lstadd_back(node, ft_lstnew((void *)str_cut((char **)(&current->content), i, 1)));
                    printf("%s %s\n", (char *)current->content, (char *)current->next->content);
                    //get_treeline(&current->next, &get_closing_parenthesis);
                    break;
                }
                else
                {
                    ft_lstadd_back(node, ft_lstnew((void *)str_cut((char **)(&current->content), i, 2)));
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

// void	t_node *get_tree(t_var *var, char *inputline, t_list *t_node)
// {
//     int i;
    
//     /* fill firdt var with node content*/
//     i = -1;
//     while (inputline[++i])
//     {
//         if (/* is AND */)
//         {
//             /*fill var next_success: ft_lstaddlast_back(ft_lstnew_node(node->next))*/
//             /*fill var next_failure: NULL:*/
//             /*interate: node = node->next; var->tokens = var->tokens->next_sucess*/ 
//         }
//         else if (/* is OR */)
//         {
//             /*fill var next_success: NULL:*/
//             /*fill var next_failure: ft_lstaddlast_back(ft_lstnew_node(node->next))*/
//             /*interate: node = node->next; var->tokens = var->tokens->next_sucess*/ 
//         }
//     }
// }



// #include <stdio.h>

// int main(int argc, char **argv)
// {
//     char *line;
//     t_list *lst;
//     t_list *current;

//     line = ft_strdup(argv[1]);
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
//         return 1;
//     }
//     lst = ft_lstnew(line);
//     get_tree(&lst, should_cut);
//     printf("MAIN FUNCTION\n");
//     current = lst;
//     while (current)
//     {
//         printf("%s\n", ((char *)current->content));
//         current = current->next;
//     }
//     ft_lstclear(&lst, free);
//     return 0;
// }