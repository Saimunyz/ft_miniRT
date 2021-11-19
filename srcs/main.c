/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:02:22 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/02 00:33:23 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data	ft_init_data(void)
{
	t_data	data;

	data.a.intens = 0;
	data.cam_begin = NULL;
	data.cams = NULL;
	data.l = NULL;
	data.obj = NULL;
	return (data);
}

int		ft_render(t_data *f)
{
	t_vect		ray;
	double		x;
	double		y;
	int			color;

	y = 0;
	f->mlx.img = mlx_new_image(f->mlx.mlx, f->win.w, f->win.h);
	f->mlx.addr = mlx_get_data_addr(f->mlx.img, &f->mlx.bpp,
			&f->mlx.ll, &f->mlx.endian);
	while (y < f->win.h)
	{
		x = 0;
		while (x < f->win.w)
		{
			ray = ft_get_ray(f->win, f->cams, x, y);
			color = ft_trace_ray(f, ray);
			my_mlx_pixel_put(f, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int		ft_print_error(int type)
{
	ft_putstr_fd("Error\n", 2);
	if (type == ARG_ERR)
		ft_putstr_fd("ARG_ERR\n", 2);
	else if (type == SAVE_ERR)
		ft_putstr_fd("Second arg must be '--save'\n", 2);
	else if (type == FILENAME_ERR)
		ft_putstr_fd("File not found\n", 2);
	else if (type == INVALID_MAP_ERR)
		ft_putstr_fd("Map error - something wrong in your .rt file\n", 2);
	else if (type == BMP_ERR)
		ft_putstr_fd("Something goes wrong while creating .bmp file\n", 2);
	else if (type == INCOMPLITE_MAP_ERR)
		ft_putstr_fd("Not enough elements in .rt file\n", 2);
	else
		ft_putstr_fd("UNKNOWN_ERR\n", 2);
	return (type);
}

int		ft_minirt(int argc, char **argv, t_data *d)
{
	int		err;

	err = 0;
	d->mlx.mlx = mlx_init();
	mlx_get_screen_size(d->mlx.mlx, &d->win.max_w, &d->win.max_h);
	if ((err = ft_parse(argv[1], d)) != 0)
		return (err);
	if ((err = ft_check_data(d)) != 0)
		return (err);
	d->cam_begin = d->cams;
	ft_render(d);
	if (argc == 3)
		err = ft_save_bmp(d);
	else
	{
		d->mlx.win = mlx_new_window(d->mlx.mlx, d->win.w, d->win.h, "miniRT");
		mlx_put_image_to_window(d->mlx.mlx, d->mlx.win, d->mlx.img, 0, 0);
		mlx_destroy_image(d->mlx.mlx, d->mlx.img);
		ft_start_hooks(d);
		mlx_loop(d->mlx.mlx);
		mlx_destroy_window(d->mlx.mlx, d->mlx.win);
	}
	ft_free_data(d);
	return (err);
}

int		main(int argc, char **argv)
{
	t_data	data;
	int		err;
	char	*f;

	err = 0;
	if (argc != 2 && argc != 3)
		return (ft_print_error(ARG_ERR));
	if (argc == 3 && (ft_strncmp(argv[2], "--save", ft_strlen(argv[2]))) != 0)
		return (ft_print_error(SAVE_ERR));
	if (!(f = ft_strnstr(argv[1], ".rt\0", ft_strlen(argv[1]))))
		return (ft_print_error(ARG_ERR));
	if (f && *(f + 3) != '\0')
		return (ft_print_error(ARG_ERR));
	data = ft_init_data();
	err = ft_minirt(argc, argv, &data);
	return (err);
}
