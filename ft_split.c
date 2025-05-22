/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/22 13:48:20 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	update_counters(char const *s1, char c, int *array,
		size_t counter[3])
{
	if (s1[counter[0]] != c)
	{
		counter[2]++;
		if (counter[2] == 1)
			counter[1]++;
	}
	else
	{
		counter[2] = 0;
	}
	array[counter[0]] = counter[1];
}

static int	ft_searchm(char const *s1, char c, size_t len, int *array)
{
	int		j;
	size_t	counter[3];

	j = 0;
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	while (s1[counter[0]])
	{
		if (s1[counter[0]] == c)
		{
			array[len + j] = counter[2];
			counter[2] = 0;
			array[counter[0]] = -1;
			if ((counter[0] > 0 && array[counter[0] - 1] != -1)
				&& counter[0] != len - 1)
				j++;
		}
		else
			update_counters(s1, c, array, counter);
		if (counter[0] == len - 1 && counter[2] != 0)
			array[len + j] = counter[2];
		counter[0]++;
	}
	return (j);
}

char	**ft_mallocstr(size_t len, int *array, size_t j)
{
	size_t	i;
	char	**str;

	str = malloc((j + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i <= j)
	{
		str[i] = malloc(array[len + i] * sizeof(char));
		if (!str[i])
			return (NULL);
		i++;
	}
	if (len == 0 && j == 0)
		str[0] = NULL;
	str[j + 1] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	int		*array;
	size_t	j;
	char	**str;
	int		counter;

	len = ft_strlen((char *)s);
	array = malloc(2 * len * sizeof(int));
	if (!array)
		return (NULL);
	j = ft_searchm(s, c, len, array);
	str = ft_mallocstr(len, array, j);
	counter = 0;
	j = 0;
	while (j < len)
	{
		if (array[j] > 0)
			str[array[j] - 1][counter] = s[j];
		else
			counter = -1;
		j++;
		counter++;
	}
	free(array);
	return (str);
}
