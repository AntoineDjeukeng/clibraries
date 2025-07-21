/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:43:47 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 19:50:37 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Fdf.h"

t_vec3	to_screen_coords(t_Object_3d *app, t_vec3 p)
{
	t_vec3	res;
	float	tx;
	float	ty;
	float	tz;

	res.color = 0xFFFFFF;
	res.x = 0.0f;
	res.y = 0.0f;
	res.z = 0.0f;
	res.color = p.color;
	tx = p.x + app->offset.x;
	ty = p.y + app->offset.y;
	tz = p.z + app->offset.z;
	res.x = (int)(app->reference.origin.x + tx * app->reference.u.x + ty
			* app->reference.v.x + tz * app->reference.w.x);
	res.y = (int)(app->reference.origin.y + tx * app->reference.u.y + ty
			* app->reference.v.y + tz * app->reference.w.y);
	res.z = (int)(app->reference.origin.z + tx * app->reference.u.z + ty
			* app->reference.v.z + tz * app->reference.w.z);
	return (res);
}

int	interpolate_color(int color_start, int color_end, float t)
{
	int	r;
	int	g;
	int	b;

	r = ((color_start >> 16) & 0xFF) + (int)((((color_end >> 16) & 0xFF)
				- ((color_start >> 16) & 0xFF)) * t);
	g = ((color_start >> 8) & 0xFF) + (int)((((color_end >> 8) & 0xFF)
				- ((color_start >> 8) & 0xFF)) * t);
	b = (color_start & 0xFF) + (int)(((color_end & 0xFF) - (color_start & 0xFF))
			* t);
	return ((r << 16) | (g << 8) | b);
}

void	ft_put_pixel(t_Object_3d *app, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = app->img_data + (y * app->size_line + x * (app->bpp / 8));
	pixel[0] = color & 0xFF;
	pixel[1] = (color >> 8) & 0xFF;
	pixel[2] = (color >> 16) & 0xFF;
	if (app->bpp == 32)
		pixel[3] = 0;
}

void	draw_line_gradient_to_image(t_Object_3d *app, t_vec3 p0, t_vec3 p1)
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	int		i;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	if (fabsf(dx) > fabsf(dy))
		steps = fabsf(dx);
	else
		steps = fabsf(dy);
	x = p0.x;
	i = 0;
	while (i <= (int)steps)
	{
		ft_put_pixel(app, (int)(x + 0.5f), (int)(p0.y + dy / steps * i + 0.5f),
			interpolate_color(p0.color, p1.color, (float)i / steps));
		x += dx / steps;
		i++;
	}
}

void	draw_cube_to_image(t_Object_3d *app)
{
	int		i;
	t_vec3	p_start;
	t_vec3	p_end;

	i = 0;
	while (i < app->edge_count)
	{
		p_start = app->vertices[app->edges[i].start];
		p_end = app->vertices[app->edges[i].end];
		p_start = to_screen_coords(app, p_start);
		p_end = to_screen_coords(app, p_end);
		draw_line_gradient_to_image(app, p_start, p_end);
		i++;
	}
}
