/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:05:47 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/23 18:33:53 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *ptr;
    size_t ls = ft_strlen(s);
    size_t substr_len;
    size_t i;

    if (start >= ls)
        return strdup(""); // Return empty string if start out of range

    if (ls - start < len)
        substr_len = ls - start;
    else
        substr_len = len;

    ptr = malloc(substr_len + 1);
    if (!ptr)
        return NULL;

    i = 0;
    while (i < substr_len)
    {
        ptr[i] = s[start + i];
        i++;
    }
    ptr[i] = '\0';

    return ptr;
}
