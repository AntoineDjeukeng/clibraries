/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:48:52 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 19:57:47 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

void	init_reference_scaled(t_Object_3d *app)
{
	t_vec3	ux;
	t_vec3	uy;
	t_vec3	uz;

	ux.x = app->unit_scale.x * app->zoom;
	ux.y = 0;
	ux.z = 0;
	ux.color = 0;
	uy.x = 0;
	uy.y = app->unit_scale.y * app->zoom;
	uy.z = 0;
	uy.color = 0;
	uz.x = 0;
	uz.y = 0;
	uz.z = app->unit_scale.z * app->zoom;
	uz.color = 0;
	app->reference.u = rotate_xyz(ux, app->angle_x, app->angle_y, app->angle_z);
	app->reference.v = rotate_xyz(uy, app->angle_x, app->angle_y, app->angle_z);
	app->reference.w = rotate_xyz(uz, app->angle_x, app->angle_y, app->angle_z);
}

void	draw_line(t_Object_3d *app, const char *line, int line_num)
{
	int	x;
	int	y;
	int	color;

	x = 10;
	y = 10 + line_num * 20;
	color = 0xFFFFFF;
	mlx_string_put(app->mlx, app->win, x, y, color, (char *)line);
}

int	render_loop(void *param)
{
	t_Object_3d	*app;

	app = (t_Object_3d *)param;
	ft_memset(app->img_data, 0, HEIGHT * app->size_line);
	init_reference_scaled(app);
	draw_cube_to_image(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (0);
}

int	close_window(void *param)
{
	t_Object_3d	*app;

	app = (t_Object_3d *)param;
	mlx_destroy_window(app->mlx, app->win);
	exit(0);
	return (0);
}
