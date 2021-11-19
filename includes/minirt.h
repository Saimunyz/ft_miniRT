/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:40:45 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/02 00:33:11 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "get_next_line.h"
# include "libft.h"
# include "math.h"
# include "fcntl.h"
# include "mlx.h"

# define ESC 0xFF1B
# define LEFT 0xFF51
# define RIGHT 0xFF53
# define INF 4294967295
# define PI 3.14159265
# define EPS 0.0001

# define ARG_ERR 1
# define SAVE_ERR 2
# define FILENAME_ERR 3
# define INVALID_MAP_ERR 4
# define BMP_ERR 5
# define INCOMPLITE_MAP_ERR 6

typedef struct	s_vect
{
	double x;
	double y;
	double z;
}				t_vect;

typedef struct	s_plane
{
	t_vect			center;
	t_vect			normal;
	int				color;
}				t_plane;

typedef struct	s_sphere
{
	t_vect			center;
	double			r;
	int				c;
}				t_sphere;

typedef struct	s_square
{
	t_vect	center;
	t_vect	normal;
	double	h;
	int		color;
}				t_square;

typedef struct	s_triangle
{
	t_vect	p1;
	t_vect	p2;
	t_vect	p3;
	int		color;
}				t_triangle;

typedef struct	s_cylinder
{
	t_vect	cent;
	t_vect	norm;
	double	r;
	double	h;
	int		color;
}				t_cylinder;

typedef struct	s_amb
{
	double		intens;
	int			color;
}				t_amb;

typedef struct	s_light
{
	double			i;
	int				color;
	t_vect			p;
	struct s_light	*next;
}				t_light;

enum			e_obj
{
	PLANE,
	SQUARE,
	SPHERE,
	TRIANGLE,
	CYLINDER
};

union			u_obj
{
	t_sphere	sp;
	t_plane		pl;
	t_square	sq;
	t_triangle	tr;
	t_cylinder	cy;
};

typedef struct	s_obj
{
	enum e_obj		type;
	union u_obj		obj;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_intersection
{
	double		t;
	double		t_1;
	double		t_2;
	t_vect		point;
	t_vect		origin;
	t_vect		normal;
	int			color;
	int			is_hit;
}				t_inter;

typedef struct	s_camera
{
	t_vect			center;
	t_vect			normal;
	double			fov;
	struct s_camera	*next;
}				t_camera;

typedef struct	s_win
{
	int		max_w;
	int		max_h;
	int		w;
	int		h;
}				t_win;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_mlx;

typedef struct	s_data
{
	t_mlx		mlx;
	t_win		win;
	t_amb		a;
	t_light		*l;
	t_camera	*cams;
	t_camera	*cam_begin;
	t_obj		*obj;
}				t_data;

int				create_trgb(int t, int r, int g, int b);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
double			ft_len_v(t_vect v);
t_vect			ft_normolize_vect(t_vect v);
t_vect			ft_add_vect(t_vect v1, t_vect v2);
t_vect			ft_mult_vect_s(double scalar, t_vect v);
t_vect			ft_zero_vect(void);
t_vect			ft_create_vect(double x, double y, double z);
double			ft_mult_vect(t_vect v1, t_vect v2);
t_vect			ft_sub_vect(t_vect v1, t_vect v2);
t_vect			ft_cross_v(t_vect v1, t_vect v2);

void			ft_start_hooks(t_data *data);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

t_vect			ft_get_ray(t_win win, t_camera *cam, double x, double y);
int				ft_trace_ray(t_data *f, t_vect d);
int				ft_comp_light(t_data *f, t_light *light, t_inter inter);

t_camera		*ft_create_cam(t_vect center, t_vect normal, double fov);
void			ft_add_camera(t_camera **lst, t_camera *new);
int				ft_lst_camera_size(t_camera *cam);
void			ft_clear_camera(t_camera **cam);
t_vect			ft_cam_direction(t_vect o, t_vect normal);

t_sphere		ft_create_sphere(t_vect center, double r, int color);
t_plane			ft_create_plane(t_vect center, t_vect normal, int color);
t_square		ft_create_square(t_vect center, double h, int color, t_vect n);
t_cylinder		ft_create_cylinder(t_vect center, t_vect n, double dia,
					double h);
t_triangle		ft_create_triangle(t_vect p1, t_vect p2, t_vect p3, int color);

int				ft_intersect_ray_sphere(t_inter *inter, t_vect d, t_sphere s);
int				ft_intersect_ray_plane(t_inter *in, t_vect d, t_vect p,
					t_vect n);
int				ft_intersect_ray_square(t_inter *inter, t_vect d, t_square sq);
int				ft_intersect_ray_cylinder(t_inter *in, t_vect d, t_cylinder cy);
int				ft_intersect_ray_triangle(t_inter *inter, t_vect d,
					t_triangle tr);

t_light			*ft_create_light(double intens, t_vect p, int color);
t_amb			ft_create_ambient(double intens, int color);
void			ft_add_light(t_light **lst, t_light *new);
void			ft_clear_light(t_light **l);
int				ft_lst_light_size(t_light *l);

t_vect			ft_reflect_ray(t_vect v1, t_vect v2);
void			ft_calc_ray(t_inter *inter, t_vect d);

double			ft_min(double n1, double n2);
double			ft_max(double n1, double n2);
double			ft_abs(double n);
t_inter			ft_init_inter(t_vect origin);

t_obj			*ft_new_obj(enum e_obj type, void *data);
void			ft_add_obj(t_obj **lst, t_obj *new);
void			ft_clear_obj(t_obj **obj);
int				ft_lst_obj_size(t_obj *obj);

void			ft_closest_sphere(t_vect d, t_inter *inter, t_obj *obj);
void			ft_closest_plane(t_vect d, t_inter *inter, t_obj *obj);
void			ft_closest_square(t_vect d, t_inter *inter, t_obj *obj);
void			ft_closest_triangle(t_vect d, t_inter *inter, t_obj *obj);
void			ft_closest_cylinder(t_vect d, t_inter *inter, t_obj *obj);

int				ft_add_color(int color1, int color2);
int				ft_sub_color(int color1, int color2);
int				ft_mult_color(int color1, int color2);
int				ft_mult_color_s(int color, double scalar);
int				ft_add_lights(int color1, int color2);

int				ft_save_bmp(t_data *data);
int				ft_print_error(int type);
int				ft_render(t_data *f);
void			ft_free_data(t_data *data);
int				ft_check_data(t_data *data);

int				ft_parse_color(char *line, int *color);
int				ft_parse(char *filename, t_data *data);
int				ft_parse_vect(char *line, t_vect *vect);
int				ft_parse_norm(char *line, t_vect *norm);

int				ft_set_triangle(char *line, t_data *data);
int				ft_set_light(char *line, t_data *data);
int				ft_set_sphere(char *line, t_data *data);
int				ft_set_plane(char *line, t_data *data);
int				ft_set_square(char *line, t_data *data);
int				ft_set_cylinder(char *line, t_data *data);
int				ft_set_cam(char *line, t_data *data);
int				ft_set_res(char *line, t_data *data);
int				ft_set_amb(char *line, t_data *data);

#endif
