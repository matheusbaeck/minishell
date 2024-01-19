/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy2dpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:45:02 by smagniny          #+#    #+#             */
/*   Updated: 2023/11/30 13:51:31 by smagniny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function to copy a null-terminated 2D array
char** copy_2d_array(const char** original)
{
    int     num_rows;
    char    **copy;
    int     i;

    i = 0;
    num_rows = 0;
    while (original[num_rows] != NULL)
        num_rows++;
    copy = (char**)malloc((num_rows + 1) * sizeof(char*));
    if (copy == NULL)
        return (NULL);
    while (i < num_rows)
    {
        copy[i] = ft_strdup(original[i]);
        if (copy[i] == NULL)
        {
            doublefree(copy);
            return (NULL);
        }
        i++;
    }
    copy[num_rows] = NULL;
    return (copy);
}