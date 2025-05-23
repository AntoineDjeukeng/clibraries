/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:26:02 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/23 20:41:45 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memchr(const void *s, int c, size_t n)
// {
// 	const unsigned char	*src;
// 	size_t				i;

// 	i = 0;
// 	src = (const unsigned char *)s;
// 	while (i < n)
// 	{
// 		if (src[i] == c)
// 		{
// 			return ((void *)(src + i));
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src = (const unsigned char *)s;
	size_t				i = 0;

	while (i < n)
	{
		if (src[i] == (unsigned char)c)  // cast c here
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
