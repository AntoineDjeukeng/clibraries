/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:09 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 12:52:36 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_lstrompt(char const *s1, int *array, int count)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(count * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (array[i] == 1)
		{
			str[j] = s1[i];
			j++;
		}
		i++;
	}
	free(array);
	return (&str[0]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ls1;
	size_t	i;
	ssize_t	count;
	int		*array;

	ls1 = ft_strlen((char *)s1);
	array = malloc(ls1 * sizeof(int));
	i = 0;
	count = 0;
	while (s1[i])
	{
		if (ft_inset((char *)set, s1[i]) == 1)
		{
			count++;
			array[i] = 0;
		}
		else
			array[i] = 1;
		i++;
	}
	return (ft_lstrompt(s1, array, count));
}
