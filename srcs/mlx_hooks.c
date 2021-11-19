/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 02:11:47 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:13:53 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		ft_change_cam(int keycode, t_data *data)
{
	t_camera	*tmp;

	if (keycode == RIGHT && data->cams->next)
	{
		data->cams = data->cams->next;
		ft_render(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
			data->mlx.img, 0, 0);
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	}
	if (keycode == LEFT && data->cams != data->cam_begin)
	{
		tmp = data->cam_begin;
		while (tmp->next != data->cams && tmp->next)
			tmp = tmp->next;
		data->cams = tmp;
		ft_render(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
			data->mlx.img, 0, 0);
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	}
	return (0);
}

static int		ft_keyboard(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		ft_free_data(data);
		exit(0);
	}
	if (keycode == RIGHT || keycode == LEFT)
		ft_change_cam(keycode, data);
	return (0);
}

static int		ft_close(t_data *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	ft_free_data(data);
	exit(0);
	return (0);
}

void			ft_start_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 33, 0, ft_close, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, ft_keyboard, data);
}
