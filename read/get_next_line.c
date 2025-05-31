/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:57:11 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/31 21:13:48 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_until_newline(int fd, char *keep)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);

	while (!ft_strchr(keep, '\n'))
	{


		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		if (bytes_read == -1)
		{
			free(buf);
			free(keep);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		keep = append_buffer(keep, buf);
		if (!keep)
		{
			free(buf);
			return (NULL); // malloc failure in append
		}
	}
	free(buf);
	return (keep);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = 0;
	while (dst[dst_len] != '\0')
		dst_len++;
	i = 0;
	while (src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

char	*append_buffer(char *old, char *new_data)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(old) + ft_strlen(new_data);
	if(len>10000000)
		return (NULL);
	joined = malloc(len + 1);
	if (!joined)
	{
		free(old);
		return (NULL);
	}
	ft_strcpy(joined, old);
	ft_strcat(joined, new_data);
	free(old);
	return (joined);
}

const char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			return (s);
		s++;
	}
	if ((unsigned char)*s == uc)
		return (s);
	return (NULL);
}

// char	*get_next_line(int fd)
// {
// 	static char	*keep = NULL;
// 	const char	*pos;
// 	char		*line;
// 	size_t		len;

// 	if (!keep)
// 		keep = ft_calloc(1, 1);
// 	if (!keep)
// 		return (NULL);
// 	keep = read_until_newline(fd, keep);
// 	if (!keep)
// 		return (NULL);
// 	pos = ft_strchr(keep, '\n');
// 	if (pos)
// 		len = pos - keep + 1;
// 	else
// 		len = ft_strlen(keep);
// 	line = ft_strndup(keep, len);
// 	keep = ft_strdup(keep + len);
// 	return (line);
// }

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	    return (NULL);
	static char	*keep = NULL;
	const char	*pos;
	char		*line;
	char		*new_keep;
	size_t		len;
	if (!keep)
		keep = ft_calloc(1, 1);
	if (!keep)
		return (NULL);

	keep = read_until_newline(fd, keep);
	if (!keep || *keep == '\0')
	{
		free(keep);
		return (NULL);
	}

	pos = ft_strchr(keep, '\n');
	if (pos)
		len = pos - keep + 1;
	else
		len = ft_strlen(keep);

	line = ft_strndup(keep, len);
	if (!line)
		return (NULL);

	new_keep = ft_strdup(keep + len);
	free(keep);
	keep = new_keep;

	return (line);
}
