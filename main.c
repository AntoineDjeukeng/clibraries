/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:52:40 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/22 17:02:17 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>


int main(void)
{
    char s[] = {0, 1, 2, 3, 4, 5};
    unsigned char *res;

    res = (unsigned char *)ft_memchr(s, 0, 0);
    printf("1: %s\n", res ? "Found" : "Not found");

    res = (unsigned char *)ft_memchr(s, 0, 1);
    if (res)
        printf("2: Found value: %d\n", *res);
    else
        printf("2: Not found\n");

    res = (unsigned char *)ft_memchr(s, 2, 3);
    if (res)
        printf("3: Found value: %d\n", *res);
    else
        printf("3: Not found\n");

    res = (unsigned char *)ft_memchr(s, 6, 6);
    if (res)
        printf("4: Found value: %d\n", *res);
    else
        printf("4: Not found\n");

    res = (unsigned char *)ft_memchr(s, 2 + 2256, 3);
    if (res)
        printf("5: Found value: %d\n", *res);
    else
        printf("5: Not found\n");

    return 0;
}
