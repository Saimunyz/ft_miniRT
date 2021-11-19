/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:17:24 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:41:34 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_triangle	ft_create_triangle(t_vect p1, t_vect p2, t_vect p3, int color)
{
	t_triangle	tr;

	tr.p1 = p1;
	tr.p2 = p2;
	tr.p3 = p3;
	tr.color = color;
	return (tr);
}

int			ft_is_inside(t_triangle tr, t_vect p, t_vect n)
{
	t_vect	edge1;
	t_vect	edge2;
	t_vect	edge3;
	t_vect	c;

	edge1 = ft_sub_vect(tr.p2, tr.p1);
	edge2 = ft_sub_vect(tr.p3, tr.p2);
	edge3 = ft_sub_vect(tr.p1, tr.p3);
	c = ft_sub_vect(p, tr.p1);
	if (ft_mult_vect(n, ft_cross_v(edge1, c)) < EPS)
		return (0);
	c = ft_sub_vect(p, tr.p2);
	if (ft_mult_vect(n, ft_cross_v(edge2, c)) < EPS)
		return (0);
	c = ft_sub_vect(p, tr.p3);
	if (ft_mult_vect(n, ft_cross_v(edge3, c)) < EPS)
		return (0);
	return (1);
}

int			ft_intersect_ray_triangle(t_inter *inter, t_vect d, t_triangle tr)
{
	t_vect	a;
	t_vect	b;
	t_vect	p;
	t_vect	normal;
	double	t_prev;

	a = ft_sub_vect(tr.p2, tr.p1);
	b = ft_sub_vect(tr.p3, tr.p1);
	normal = ft_normolize_vect(ft_cross_v(a, b));
	t_prev = inter->t;
	if (ft_intersect_ray_plane(inter, d, tr.p1, normal))
	{
		p = ft_add_vect(inter->origin, ft_mult_vect_s(inter->t, d));
		if (ft_is_inside(tr, p, normal))
		{
			inter->normal = normal;
			inter->point = p;
			return (1);
		}
	}
	inter->t = t_prev;
	return (0);
}
