/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:27:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 03:50:22 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

t_vec3	rotate_xyz(t_vec3 v, float angle_x, float angle_y, float angle_z)
{
	t_vec3	r;
	float	a;
	float	b;
	float	c;

	a = cosf(angle_x);
	b = sinf(angle_x);
	c = v.y * a - v.z * b;
	r.z = v.y * b + v.z * a;
	r.y = c;
	a = cosf(angle_y);
	b = sinf(angle_y);
	c = v.x * a + r.z * b;
	r.z = -v.x * b + r.z * a;
	r.x = c;
	a = cosf(angle_z);
	b = sinf(angle_z);
	c = r.x * a - r.y * b;
	r.y = r.x * b + r.y * a;
	r.x = c;
	return (r);
}

void	handle_rotation(int keycode, t_Object_3d *app)
{
	if (keycode == XK_q)
		app->angle_x -= 1.0f * M_PI / 180.0f;
	else if (keycode == XK_e)
		app->angle_x += 1.0f * M_PI / 180.0f;
	else if (keycode == XK_w)
		app->angle_y -= 1.0f * M_PI / 180.0f;
	else if (keycode == XK_s)
		app->angle_y += 1.0f * M_PI / 180.0f;
	else if (keycode == XK_a)
		app->angle_z -= 1.0f * M_PI / 180.0f;
	else if (keycode == XK_d)
		app->angle_z += 1.0f * M_PI / 180.0f;
}

int	mouse_move(int x, int y, void *param)
{
	t_Object_3d	*app;
	int			dx;
	int			dy;

	app = (t_Object_3d *)param;
	if (!app->mouse_initialized)
	{
		app->last_mouse_x = x;
		app->last_mouse_y = y;
		app->mouse_initialized = 1;
		return (0);
	}
	dx = x - app->last_mouse_x;
	dy = y - app->last_mouse_y;
	app->angle_y += dx * 0.005f;
	app->angle_x += dy * 0.005f;
	app->last_mouse_x = x;
	app->last_mouse_y = y;
	return (0);
}
