/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:19:28 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/21 02:24:57 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.ll + x * (data->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_r(int trgb)
{
	return ((trgb & 0xFFFFFF) >> 16);
}

int		get_g(int trgb)
{
	return ((trgb & 0xFFFF) >> 8);
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}
