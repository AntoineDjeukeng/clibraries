/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:45:06 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 19:36:15 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

float	ft_absf(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	build_vertex_array(t_Object_3d *obj)
{
	t_line	*current;
	int		i;
	int		j;
	t_vec3	v;

	j = 0;
	current = obj->head;
	while (current)
	{
		i = 0;
		while (i < current->vertex_count)
		{
			v = current->vertices[i++];
			v.x -= obj->x_sum;
			v.y -= obj->y_sum;
			v.z -= obj->z_sum;
			obj->vertices[j++] = v;
			if (v.z < obj->zmin)
				obj->zmin = v.z;
			if (v.z > obj->zmax)
				obj->zmax = v.z;
		}
		current = current->next;
	}
}

void	free_obj_info(t_Object_3d *obj)
{
	if (!obj)
		return ;
	if (obj->vertices)
		free(obj->vertices);
	if (obj->head)
		free_lines(obj->head);
	free(obj);
}

t_Object_3d	*ft_int_objet3d(const char *filename)
{
	t_Object_3d	*obj;

	obj = malloc(sizeof(t_Object_3d));
	if (!obj)
		return (NULL);
	ft_init_object_3d(obj);
	read_file_lines(filename, obj);
	if (!obj->head)
	{
		free(obj);
		return (NULL);
	}
	obj->vertices = malloc(sizeof(t_vec3) * obj->vertex_count);
	if (!obj->vertices)
	{
		free_lines(obj->head);
		free(obj);
		return (NULL);
	}
	obj->x_sum /= obj->vertex_count;
	obj->y_sum /= obj->vertex_count;
	obj->z_sum /= obj->vertex_count;
	build_vertex_array(obj);
	return (obj);
}

void	read_file_lines(const char *filename, t_Object_3d *obj)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!append_line(obj, line, obj->nb_lines++))
		{
			free(line);
			return ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
