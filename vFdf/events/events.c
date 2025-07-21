/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:41:05 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 03:50:09 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

void	clear_image(t_Object_3d *app)
{
	memset(app->img_data, 0, HEIGHT * app->size_line);
}

void	handle_movement(int keycode, t_Object_3d *app)
{
	if (keycode == XK_Left)
		app->reference.origin.x -= 1.1f;
	else if (keycode == XK_Right)
		app->reference.origin.x += 1.1f;
	else if (keycode == XK_Down)
		app->reference.origin.y += 1.1f;
	else if (keycode == XK_Up)
		app->reference.origin.y -= 1.1f;
}

void	handle_recenter(int keycode, t_Object_3d *app)
{
	if (keycode == XK_1 || keycode == XK_2 || keycode == XK_3)
	{
		app->unit_scale.x = 5;
		app->unit_scale.y = 5;
		app->unit_scale.z = 3;
		app->reference.origin.x = WIDTH / 2;
		app->reference.origin.y = HEIGHT / 2;
		app->reference.origin.z = 0;
		app->angle_x = 0.0f;
		app->angle_y = 0.0f;
		app->angle_z = 0.0f;
		if (keycode == XK_1)
			app->angle_z = 0;
		else if (keycode == XK_2)
			app->angle_x = M_PI / 2;
		else if (keycode == XK_3)
			app->angle_y = M_PI / 2;
	}
}

void	handle_zoom(int keycode, t_Object_3d *app)
{
	if (keycode == XK_plus || keycode == '=')
	{
		app->unit_scale.x += 1.2f;
		app->unit_scale.y += 1.2f;
		app->unit_scale.z += 1.2f;
	}
	else if (keycode == XK_minus || keycode == '-')
	{
		app->unit_scale.x -= 1.2f;
		app->unit_scale.y -= 1.2f;
		app->unit_scale.z -= 1.2f;
	}
}

int	handle_key(int keycode, void *param)
{
	t_Object_3d	*app;

	app = (t_Object_3d *)param;
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(app->mlx, app->win);
		exit(0);
	}
	if (keycode == XK_h)
		app->show_help = !app->show_help;
	handle_movement(keycode, app);
	handle_rotation(keycode, app);
	handle_zoom(keycode, app);
	handle_recenter(keycode, app);
	return (0);
}
