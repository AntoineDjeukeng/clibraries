/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:34:02 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 19:09:24 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

void	assign_edges(t_Object_3d *list)
{
	int		i;
	int		j;
	int		k;
	t_vec3	v1;
	t_vec3	v2;

	i = 0;
	k = 0;
	while (i < list->vertex_count - 1)
	{
		v1 = list->vertices[i];
		j = i + 1;
		while (j < list->vertex_count)
		{
			v2 = list->vertices[j];
			if ((v1.x == v2.x && v1.y + 1 == v2.y) || (v1.y == v2.y && v1.x
					+ 1 == v2.x))
			{
				list->edges[k].start = i;
				list->edges[k++].end = j;
			}
			j++;
		}
		i++;
	}
}

void	build_edges_from_grid(t_Object_3d *list)
{
	int		i;
	int		j;
	t_vec3	v1;
	t_vec3	v2;

	list->edge_count = 0;
	i = 0;
	while (i < list->vertex_count - 1)
	{
		v1 = list->vertices[i];
		j = i + 1;
		while (j < list->vertex_count)
		{
			v2 = list->vertices[j];
			if ((v1.x == v2.x && v1.y + 1 == v2.y) || (v1.y == v2.y && v1.x
					+ 1 == v2.x))
				list->edge_count++;
			j++;
		}
		i++;
	}
	list->edges = malloc(sizeof(t_edge) * list->edge_count);
	if (!list->edges)
		return ;
	assign_edges(list);
}
