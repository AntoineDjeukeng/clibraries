/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:45:30 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/23 18:44:15 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	char	*str;

	i = 0;
	ls1 = ft_strlen((char *)s1);
	ls2 = ft_strlen((char *)s2);
	str = malloc((ls1 + ls2+1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < ls1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ls2)
	{
		str[i + ls1] = s2[i];
		i++;
	}
	str[i + ls1] = '\0';
	return (&str[0]);
}
