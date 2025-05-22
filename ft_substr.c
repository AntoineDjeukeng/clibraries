/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:05:47 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 12:40:30 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	ls;
	size_t	j;

	i = 0;
	ls = ft_strlen((char *)s);
	while (s[i] != (char)start)
		i++;
	if (i > ls)
		return (NULL);
	if (ls >= (len + i))
		ptr = malloc(len * sizeof(char));
	else
		ptr = malloc((ls - i) * sizeof(char));
	if (!ptr)
		return (NULL);
	j = 0;
	while ((j + i) < ls && j < len)
	{
		ptr[j] = s[j + i];
		j++;
	}
	return (&ptr[0]);
}
