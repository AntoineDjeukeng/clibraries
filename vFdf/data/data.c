/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:00:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 04:57:54 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

int	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
	return (0);
}

void	free_lines(t_line *head)
{
	t_line	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->vertices)
			free(head->vertices);
		free(head);
		head = tmp;
	}
}

int	normalize_whitespace(char ***split, char *str)
{
	int	i;
	int	count;

	if (!str || !split)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
			str[i] = ' ';
		i++;
	}
	*split = ft_split(str, ' ');
	if (!*split)
		return (0);
	count = 0;
	while ((*split)[count])
		count++;
	return (count);
}

int	ft_process_line(t_vec3 **vertices, char *line, int row, t_Object_3d *list)
{
	int		i;
	int		count;
	char	**split;

	i = 0;
	count = normalize_whitespace(&split, line);
	*vertices = malloc(sizeof(t_vec3) * count);
	if (!*vertices || count == 0)
		return (free_split(split));
	while (i < count)
	{
		(*vertices)[i].x = (double)i;
		(*vertices)[i].y = (double)row;
		(*vertices)[i].z = (double)ft_atoi(split[i]);
		(*vertices)[i].color = list->colors[1];
		if ((int)(*vertices)[i].z == 0)
			(*vertices)[i].color = list->colors[0];
		list->x_sum += i;
		list->y_sum += row;
		list->z_sum += (*vertices)[i].z;
		i++;
	}
	free_split(split);
	return (count);
}

int	append_line(t_Object_3d *list, char *line, int index)
{
	t_line	*new_node;
	int		count;

	if (index == 0)
	{
		list->x_sum = 0.0;
		list->y_sum = 0.0;
		list->z_sum = 0.0;
		list->vertex_count = 0;
	}
	new_node = malloc(sizeof(t_line));
	if (!new_node)
		return (0);
	new_node->next = NULL;
	new_node->vertices = NULL;
	count = ft_process_line(&new_node->vertices, line, index, list);
	new_node->vertex_count = count;
	list->vertex_count += count;
	if (!list->head)
		list->head = new_node;
	else
		list->tail->next = new_node;
	list->tail = new_node;
	return (1);
}
