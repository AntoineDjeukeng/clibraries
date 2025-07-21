/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:34:53 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/21 18:20:21 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>

# define M_PI 3.14159265358979323846
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define WIDTH 800
# define HEIGHT 800

typedef struct s_point3
{
	int				x;
	int				y;
	int				z;
}					t_point3;

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
	unsigned int	color;
}					t_vec3;

typedef struct s_reference
{
	t_point3		origin;
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
}					t_reference;

typedef struct s_edge
{
	int				start;
	int				end;
	struct s_edge	*next;
}					t_edge;

typedef struct s_line
{
	t_vec3			*vertices;
	int				vertex_count;
	struct s_line	*next;
}					t_line;

typedef struct s_list_info
{
	t_line			*head;
	t_line			*tail;
	t_vec3			*vertices;
	unsigned int	colors[2];
	double			x_sum;
	double			y_sum;
	double			z_sum;
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_data;
	int				nb_lines;
	double			zmin;
	double			zmax;
	int				bpp;
	int				size_line;
	int				endian;
	float			angle_x;
	float			angle_y;
	float			angle_z;
	t_vec3			unit_scale;
	t_point3		offset;
	int				last_mouse_x;
	int				last_mouse_y;
	int				mouse_initialized;
	int				show_help;
	int				flatten_z;
	float			zoom;
	int				vertex_count;
	t_edge			*edges;
	int				edge_count;
	t_reference		reference;

}					t_Object_3d;

void				build_edges_from_grid(t_Object_3d *app);
t_vec3				rotate_xyz(t_vec3 v, float angle_x, float angle_y,
						float angle_z);
int					handle_key(int keycode, void *param);
t_vec3				to_screen_coords(t_Object_3d *app, t_vec3 p);
void				draw_cube(t_Object_3d *app);
int					mouse_move(int x, int y, void *param);
int					close_window(void *param);
void				init_reference_scaled(t_Object_3d *app);

int					render_loop(void *param);

t_Object_3d			*ft_int_objet3d(const char *filename);
void				read_file_lines(const char *filename, t_Object_3d *out);
int					append_line(t_Object_3d *list, char *line, int index);
int					ft_process_line(t_vec3 **vertices, char *line, int row,
						t_Object_3d *list);
int					normalize_whitespace(char ***split, char *str);
int					free_split(char **split);
void				free_lines(t_line *head);
void				build_vertex_array(t_Object_3d *list);
int					ft_abs(int n);
float				ft_absf(float n);
void				free_obj_info(t_Object_3d *list);
void				handle_rotation(int keycode, t_Object_3d *app);
int					mouse_move(int x, int y, void *param);
void				draw_cube_to_image(t_Object_3d *app);
void				ft_init_object_3d(t_Object_3d *obj);
#endif
