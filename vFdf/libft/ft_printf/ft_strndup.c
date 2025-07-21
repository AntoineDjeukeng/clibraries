/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:43:37 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/17 11:35:58 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	j = 0;
	while (i < n && s[i])
		i++;
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (NULL);
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}
