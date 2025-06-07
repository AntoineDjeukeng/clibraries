// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_right_align.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/05 20:22:03 by adjeuken          #+#    #+#             */
// /*   Updated: 2025/06/07 01:51:48 by adjeuken         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// char *ft_pad_string(char *str, int width, char pad_char, ft_bool left_align)
// {
//     if(left_align)
//         return (ft_left_align(str, width, pad_char));
//     else
//         return (ft_right_align(str, width, pad_char));
// }

// static int pad_negative_with_zeros(char *str, char *result, int padding)
// {
//     int i;
//     int j;
    
//     i = 0;
//     j = 1;
//     if (str[0] == '-')
//         result[i++] = '-';
//     if (str[0] == '+')
//         result[i++] = '+';
//     while (i < padding + 1)
//         result[i++] = '0';
//     while (str[j])
//         result[i++] = str[j++];
//     return i;
// }

// /**
//  * ft_right_align - right-aligns a string in a new string of width n, padding with a character.
//  * @str: The original string to align. This string is freed inside the function.
//  * @n: The total width of the resulting aligned string.
//  * @c: The character used to pad the string on the right.
//  *
//  * Returns: A newly allocated string of length n with the original string right-aligned
//  * and padded on the right with character c. If allocation fails, returns NULL.
//  *
//  * Example:
//  *     ft_right_align(ft_strdup("Hi"), 5, '.') → "...Hi"
//  */

//  char *ft_right_align(char *str, int n, char c)
// {
//     int length;
//     int i;
//     int j;
//     char *result;
//     int padding;

//     length = ft_strlen(str);
//     result = ft_calloc(n + 1, sizeof(char));
//     if (!result)
//         return NULL;
//     if (n < length)
//         n = length;
//     padding = n - length;
//     i = 0;
//     j = 0;
//     if ((str[0] == '-' || str[0] == '+') && c == '0')
//         i = pad_negative_with_zeros(str, result, padding);
//     else
//     {
//         while (i < padding)
//             result[i++] = c;
//         while (i < n && str[j])
//             result[i++] = str[j++];
//     }
//     result[n] = '\0';
//     free(str);
//     return result;
// }
