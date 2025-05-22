/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:59:29 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 09:58:41 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

static char	*sft_strncat(char *dest, const char *src, size_t n)
{
	char	*start;
	size_t	i;
	size_t	l;

	start = dest;
	l = sft_strlen(dest);
	i = 0;
	while (src[i] && n > 0)
	{
		dest[l + i] = src[i];
		i++;
		n--;
	}
	dest[l + i] = '\0';
	return (start);
}

unsigned int	ft_strlcat(char *dst, char *src, unsigned int size)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	result;

	dst_len = sft_strlen(dst);
	src_len = sft_strlen(src);
	result = dst_len;
	if (!(src_len == 0 || size == 1) && (src_len < size))
	{
		result = result + src_len;
		sft_strncat(dst, src, src_len);
	}
	if (!(src_len == 0 || size == 1) && (src_len >= size))
	{
		result = result + size - 1;
		sft_strncat(dst, src, size - 1);
	}
	return (result + 1);
}
