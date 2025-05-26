/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/24 09:05:27 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char *str, char ch, int *count)
{
	int	i;

	i = 0;
	*count = 0;
	while (str[i])
	{
		if (str[i] == ch)
		{
			str[i] = '\0';
			if (i > 0 && str[i - 1] != '\0')
				(*count)++;
		}
		i++;
	}
	if (i > 0 && str[i - 1] != '\0')
		(*count)++;
	return (i);
}

int	ft_strndup(const char *src, char **segments, int j, int len)
{
	int	i;

	i = 0;
	i = 0;
	segments[j] = malloc(len + 1);
	if (!segments[j])
	{
		while (j--)
			free(segments[j]);
		return (0);
	}
	while (i < len)
	{
		segments[j][i] = src[i];
		i++;
	}
	segments[j][i] = '\0';
	return (1);
}

char	**ft_alloc_segments(char **segments, int count, int len,
		const char *str)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (i <= len)
	{
		if (str[i] == '\0')
		{
			if (i - start > 0 && j < count)
			{
				if (!ft_strndup(&str[start], segments, j, i - start))
					return (NULL);
				j++;
			}
			start = i + 1;
		}
		i++;
	}
	segments[j] = NULL;
	return (segments);
}

void	ft_free_segments(char **segments)
{
	int	i;

	i = 0;
	if (!segments)
		return ;
	while (segments[i])
	{
		free(segments[i]);
		i++;
	}
	free(segments);
}

char	**ft_split(const char *s, char c)
{
	int		count;
	int		len;
	char	**segments;
	char	*copy;

	copy = ft_strdup((char *)s);
	if (!copy)
		return (NULL);
	len = ft_count(copy, c, &count);
	segments = malloc((count + 1) * sizeof(char *));
	if (!segments)
	{
		free(copy);
		return (NULL);
	}
	if (!ft_alloc_segments(segments, count, len, copy))
	{
		free(copy);
		ft_free_segments(segments);
		return (NULL);
	}
	free(copy);
	return (segments);
}
