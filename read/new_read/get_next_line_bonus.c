/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:16:04 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/04 14:39:02 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

node_t *create_node_from_substring(node_t *node, const char *value, size_t start, size_t end)
{
    size_t i;

    if (!node || !value || start >= end)
        return (NULL);

    node->len = end - start;
    node->value = malloc(node->len + 1);
    if (!node->value)
        return (NULL);
    node->newl = 0;
    i = 0;
    while (i < node->len)
    {
        node->value[i] = value[start + i];
        if (value[start + i] == '\n')
            node->newl = 1;
        i++;
    }
    node->value[node->len] = '\0';
    node->next = NULL;
    return (node);
}


node_t	*ft_create_tail(node_t **head, node_t **tail, const char *value,
		size_t start[2])
{
	node_t	*new_node;

	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);
	new_node->newl = 0;
	new_node = create_node_from_substring(new_node, value, start[0], start[1]);
	if (!new_node)
		return (NULL);
	if (*head == NULL)
	{
		*head = new_node;
		*tail = new_node; 
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
	return (new_node);
}

char	*accumulate_until_newline(node_t **head)
{
	node_t	*next_after_accum;
	size_t	total_len;

	if (!head || !*head)
		return (NULL);
	next_after_accum = NULL;
	total_len = calculate_accum_length(*head, &next_after_accum);
	if (total_len == 0)
		return (NULL);
	return (copy_and_free_nodes(head, next_after_accum));
}

int	read_and_segment(int fd, node_t **head, node_t **tail)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	size_t	range[2];

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	range[0] = 0;
	range[1] = 0;
	while (buffer[range[1]])
	{
		if ((buffer[range[1]] == '\n' && buffer[range[1] + 1] != '\n')
			|| buffer[range[1] + 1] == '\0')
		{
			ft_create_tail(head, tail, buffer, (size_t[]){range[0], range[1]
				+ 1});
			range[0] = range[1] + 1;
		}
		range[1]++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static gnl_state_t	states[MAX_FD];
	char				*line;
	int					result;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		line = accumulate_until_newline(&states[fd].head);
		if (line)
			return (line);
		result = read_and_segment(fd, &states[fd].head, &states[fd].tail);
		if (result == -1)
		{
			free_nodes(&states[fd].head, NULL);
			states[fd].tail = NULL;
			states[fd].head = NULL;
			return (NULL);
		}
		else if (result == 0)
		{
			return (handle_eof_cleanup(&states[fd]));
		}
	}
	
}
