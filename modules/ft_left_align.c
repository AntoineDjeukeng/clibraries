// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_left_align.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/05 20:20:27 by adjeuken          #+#    #+#             */
// /*   Updated: 2025/06/07 02:07:36 by adjeuken         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// /**
//  * ft_left_align - Left-aligns a string in a new string of width n, padding with a character.
//  * @str: The original string to align. This string is freed inside the function.
//  * @n: The total width of the resulting aligned string.
//  * @c: The character used to pad the string on the right.
//  *
//  * Returns: A newly allocated string of length n with the original string left-aligned
//  * and padded on the right with character c. If allocation fails, returns NULL.
//  *
//  * Example:
//  *     ft_left_align(ft_strdup("Hi"), 5, '.') → "Hi..."
//  */
// char *ft_left_align(char *str, int n, char c)
// {
//     int length ;
//     char *result;
//     int i ;

//     length = ft_strlen(str);
//     result = ft_calloc(n + 1, sizeof(char));
//     i = 0;
//     if (!result)
//         return NULL;
//     while (i < length && i < n)
//     {
//         result[i] = str[i];
//         i++;
//     }
//     while (i < n)
//     {
//         result[i] = c;
//         i++;
//     }
//     result[n] = '\0';
//     free(str);
//     return result;
// }
