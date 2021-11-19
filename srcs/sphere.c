/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:36:10 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/28 16:35:46 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	ft_create_sphere(t_vect center, double r, int color)
{
	t_sphere	s;

	s.center.x = center.x;
	s.center.y = center.y;
	s.center.z = center.z;
	s.r = r;
	s.c = color;
	return (s);
}

int			ft_intersect_ray_sphere(t_inter *inter, t_vect d, t_sphere s)
{
	t_vect	oc;
	double	descr;
	double	k1;
	double	k2;
	double	k3;

	oc = ft_sub_vect(inter->origin, s.center);
	k1 = ft_mult_vect(d, d);
	k2 = 2.0 * ft_mult_vect(oc, d);
	k3 = ft_mult_vect(oc, oc) - s.r * s.r;
	descr = k2 * k2 - 4.0 * k1 * k3;
	if (descr < EPS)
		return (0);
	inter->t_1 = (-k2 - sqrt(descr)) / (2.0 * k1);
	inter->t_2 = (-k2 + sqrt(descr)) / (2.0 * k1);
	if (inter->t_1 < EPS || inter->t_2 < EPS)
		return (0);
	if (inter->t_1 < inter->t && inter->t_1 < inter->t_2)
		inter->t = inter->t_1;
	else if (inter->t_2 < inter->t)
		inter->t = inter->t_2;
	else
		return (0);
	return (1);
}
