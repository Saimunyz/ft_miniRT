/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:49:57 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:40:59 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_square	ft_create_square(t_vect center, double h, int color, t_vect n)
{
	t_square	sq;

	sq.center = center;
	sq.normal = n;
	sq.h = h;
	sq.color = color;
	return (sq);
}

int			ft_check_sides(t_square sq, t_vect ray)
{
	t_vect		up_vect;
	t_vect		right;
	t_vect		up;
	double		limx;
	double		limy;

	up_vect = ft_create_vect(0, 1, 0);
	if (sq.normal.y == 1)
		right = ft_create_vect(1, 0, 0);
	else if (sq.normal.y == -1)
		right = ft_create_vect(-1, 0, 0);
	else
		right = ft_cross_v(up_vect, ft_normolize_vect(sq.normal));
	up = ft_normolize_vect(ft_cross_v(sq.normal, right));
	limx = ft_mult_vect(ray, right);
	limy = ft_mult_vect(ray, up);
	if (ft_abs(limx) > sq.h / 2.0 || ft_abs(limy) > sq.h / 2.0)
		return (0);
	return (1);
}

int			ft_intersect_ray_square(t_inter *inter, t_vect d, t_square sq)
{
	t_vect	ray;
	double	t_prev;

	t_prev = inter->t;
	if (ft_intersect_ray_plane(inter, d, sq.center, sq.normal))
	{
		ray = ft_add_vect(inter->origin, ft_mult_vect_s(inter->t, d));
		ray = ft_sub_vect(ray, sq.center);
		if (ft_check_sides(sq, ray))
			return (1);
	}
	inter->t = t_prev;
	return (0);
}
