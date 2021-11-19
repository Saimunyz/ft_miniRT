/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:16:07 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:13:28 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_add_color(int color1, int color2)
{
	int		color;
	double	r;
	double	g;
	double	b;

	r = ft_min(get_r(color1) + get_r(color2), 255);
	g = ft_min(get_g(color1) + get_g(color2), 255);
	b = ft_min(get_b(color1) + get_b(color2), 255);
	color = create_trgb(255, r, g, b);
	return (color);
}

int		ft_sub_color(int color1, int color2)
{
	int		color;
	double	r;
	double	g;
	double	b;

	r = get_r(color1) - get_r(color2);
	g = get_g(color1) - get_g(color2);
	b = get_b(color1) - get_b(color2);
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	color = create_trgb(255, r, g, b);
	return (color);
}

int		ft_mult_color_s(int color, double scalar)
{
	double	r;
	double	g;
	double	b;

	r = get_r(color) * scalar;
	g = get_g(color) * scalar;
	b = get_b(color) * scalar;
	color = create_trgb(255, r, g, b);
	return (color);
}

int		ft_mult_color(int color1, int color2)
{
	int		color;
	double	r;
	double	g;
	double	b;

	r = get_r(color1) * (get_r(color2) / 255.0);
	g = get_g(color1) * (get_g(color2) / 255.0);
	b = get_b(color1) * (get_b(color2) / 255.0);
	color = create_trgb(255, r, g, b);
	return (color);
}
