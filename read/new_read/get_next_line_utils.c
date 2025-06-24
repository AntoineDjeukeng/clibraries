/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:45:30 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/04 14:39:09 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_nodes(node_t **head, node_t *end)
{
	node_t	*current;
	node_t	*next;

	current = *head;
	while (current != end)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
	*head = end;
}

void	copy_nodes_to_buffer(node_t *start, node_t *end, char *buffer)
{
	size_t	pos;
	size_t	i;
	node_t	*current;

	pos = 0;
	current = start;
	while (current != end)
	{
		i = 0;
		while (i < current->len)
		{
			buffer[pos++] = current->value[i++];
		}
		current = current->next;
	}
	buffer[pos] = '\0';
}

char	*copy_and_free_nodes(node_t **head, node_t *end)
{
	size_t	total_len;
	node_t	*temp;
	char	*accum_str;

	total_len = 0;
	temp = *head;
	while (temp != end)
	{
		total_len += temp->len;
		temp = temp->next;
	}
	if (total_len == 0)
		return (NULL);
	accum_str = malloc(total_len + 1);
	if (!accum_str)
		return (NULL);
	copy_nodes_to_buffer(*head, end, accum_str);
	free_nodes(head, end);
	return (accum_str);
}

size_t	calculate_accum_length(node_t *start, node_t **next_after_accum)
{
	size_t	total_len;
	node_t	*temp;

	total_len = 0;
	temp = start;
	while (temp && !temp->newl)
	{
		total_len += temp->len;
		temp = temp->next;
	}
	if (temp && temp->newl)
	{
		total_len += temp->len;
		temp = temp->next;
	}
	if (next_after_accum)
		*next_after_accum = temp;
	return (total_len);
}
char *handle_eof_cleanup(gnl_state_t *state)
{
    char *leftover = NULL;

    // Only free if head is not NULL
    if (state->head)
    {
        leftover = copy_and_free_nodes(&state->head, NULL);
        state->head = NULL;
        state->tail = NULL;
    }
    // If head is NULL, assume no nodes allocated, so do nothing
    return leftover;
}
