/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:39:09 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 19:58:59 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fdf.h"

void	ft_init_object_3d(t_Object_3d *obj)
{
	if (!obj)
		return ;
	ft_memset(obj, 0, sizeof(t_Object_3d));
	obj->zmin = INT_MAX;
	obj->zmax = INT_MIN;
	obj->unit_scale = (t_vec3){.x = 5.0f, .y = 5.0f, .z = 1.0f, .color = 0};
	obj->offset = (t_point3){0, 0, 0};
	obj->reference = (t_reference){.u = {.x = 1, .y = 0, .z = 0, .color = 0},
		.v = {.x = 0, .y = 1, .z = 0, .color = 0}, .w = {.x = 0, .y = 0, .z = 1,
		.color = 0}};
	obj->colors[0] = 0xFFFFFF;
	obj->colors[1] = 0x800080;
	obj->zoom = 1.0f;
	obj->angle_x = 0.0f;
	obj->angle_y = 0.0f;
	obj->angle_z = 0.0f;
	obj->flatten_z = 0;
	obj->last_mouse_x = 0;
	obj->last_mouse_y = 0;
	obj->mouse_initialized = 0;
	obj->show_help = 0;
	obj->reference.origin.x = WIDTH / 2;
	obj->reference.origin.y = HEIGHT / 2;
	obj->reference.origin.z = 0;
}

int	main(void)
{
	t_Object_3d	*obj;

	obj = ft_int_objet3d("test.txt");
	if (!obj)
		return (1);
	build_edges_from_grid(obj);
	if (!obj->edges)
	{
		free_obj_info(obj);
		return (1);
	}
	obj->mlx = mlx_init();
	obj->win = mlx_new_window(obj->mlx, WIDTH, HEIGHT, "FDF Grid Viewer");
	obj->img = mlx_new_image(obj->mlx, WIDTH, HEIGHT);
	obj->img_data = mlx_get_data_addr(obj->img, &obj->bpp, &obj->size_line,
			&obj->endian);
	init_reference_scaled(obj);
	mlx_hook(obj->win, 6, 1L << 6, mouse_move, obj);
	mlx_hook(obj->win, 2, 1L << 0, handle_key, obj);
	mlx_hook(obj->win, 17, 0, close_window, obj);
	mlx_loop_hook(obj->mlx, render_loop, obj);
	mlx_loop(obj->mlx);
	return (0);
}
