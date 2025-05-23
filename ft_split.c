/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/23 19:59:18 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_newstr
{
	char			*str;
	size_t			len;
	struct s_newstr	*next;
}	t_newstr;

t_newstr *create_newstr(char *str, size_t len)
{
	t_newstr *newstr = malloc(sizeof(t_newstr));
	if (!newstr)
		return NULL;
	newstr->str = str;
	newstr->len = len;
	newstr->next = NULL;
	return newstr;
}

// Free linked list
void free_newstr_list(t_newstr *head)
{
	t_newstr *tmp;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

// Count nodes in linked list
size_t count_nodes(t_newstr *head)
{
	size_t count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return count;
}

// Convert linked list to NULL-terminated array of strings (allocated)
static char **list_to_array(t_newstr *head)
{
	size_t count = count_nodes(head);
	char **arr = malloc(sizeof(char *) * (count + 1));
	size_t i = 0;

	while (head)
	{
		char *str = malloc(head->len + 1);
		if (!str)
		{
			// Free allocated so far
			while (i > 0)
			{
				free(arr[--i]);
			}
			free(arr);
			return NULL;
		}
		memcpy(str, head->str, head->len);
		str[head->len] = '\0';
		arr[i++] = str;
		head = head->next;
	}
	arr[i] = NULL;
	
	return arr;
}

// Your ft_split function using short helpers
char **ft_split(const char *s, char c)
{
	t_newstr *head = NULL;
	t_newstr *current = NULL;
	size_t start = 0, i = 0;

	while (1)
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (i > start)
			{
				t_newstr *node = create_newstr((char *)(s + start), i - start);
				if (!head)
					head = node;
				else
					current->next = node;
				current = node;
			}
			start = i + 1;
		}
		if (s[i] == '\0')
			break;
		i++;
	}
	char **result = list_to_array(head);
	free_newstr_list(head);
	return result;
}