/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 07:28:00 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 08:56:55 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			total;
	void			*ptr;
	unsigned char	*array;

	total = nmemb * size;
	i = 0;
	if (size != 0 && total > __PTRDIFF_MAX__)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	array = (unsigned char *)ptr;
	while (i < total)
	{
		array[i] = 0;
		i++;
	}
	return (ptr);
}
