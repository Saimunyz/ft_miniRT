/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:02:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/23 17:46:58 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	ft_create_plane(t_vect center, t_vect normal, int color)
{
	t_plane	pl;

	pl.center = center;
	pl.normal = normal;
	pl.color = color;
	return (pl);
}

int		ft_intersect_ray_plane(t_inter *inter, t_vect d, t_vect p, t_vect n)
{
	t_vect	co;
	double	k1;
	double	k2;
	double	t;

	k2 = ft_mult_vect(n, d);
	if (ft_abs(k2) > EPS)
	{
		co = ft_sub_vect(p, inter->origin);
		k1 = ft_mult_vect(n, co);
		t = k1 / k2;
		if (t > EPS && inter->t > t)
		{
			inter->t = t;
			return (1);
		}
	}
	return (0);
}
