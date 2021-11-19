/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:28:57 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:36:50 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_closest_sphere(t_vect d, t_inter *inter, t_obj *obj)
{
	t_sphere sp;

	sp = obj->obj.sp;
	if (ft_intersect_ray_sphere(inter, d, sp))
	{
		inter->is_hit = 1;
		inter->color = sp.c;
		inter->point = ft_add_vect(inter->origin, ft_mult_vect_s(inter->t, d));
		inter->normal = ft_sub_vect(inter->point, sp.center);
		inter->normal = ft_normolize_vect(inter->normal);
	}
}

void	ft_closest_plane(t_vect d, t_inter *inter, t_obj *obj)
{
	t_plane pl;

	pl = obj->obj.pl;
	if (ft_intersect_ray_plane(inter, d, pl.center, pl.normal))
	{
		inter->is_hit = 1;
		inter->color = pl.color;
		inter->normal = pl.normal;
		if (ft_mult_vect(d, inter->normal) > EPS)
			inter->normal = ft_mult_vect_s(-1, inter->normal);
		inter->point = ft_add_vect(inter->origin, ft_mult_vect_s(inter->t, d));
		inter->normal = ft_normolize_vect(inter->normal);
	}
}

void	ft_closest_square(t_vect d, t_inter *inter, t_obj *obj)
{
	t_square sq;

	sq = obj->obj.sq;
	if (ft_intersect_ray_square(inter, d, sq))
	{
		inter->is_hit = 1;
		inter->color = sq.color;
		inter->normal = sq.normal;
		if (ft_mult_vect(d, inter->normal) > EPS)
			inter->normal = ft_mult_vect_s(-1, inter->normal);
		inter->point = ft_add_vect(inter->origin, ft_mult_vect_s(inter->t, d));
		inter->normal = ft_normolize_vect(inter->normal);
	}
}

void	ft_closest_cylinder(t_vect d, t_inter *inter, t_obj *obj)
{
	t_cylinder	cy;
	t_vect		tmp;
	double		tmp2;

	cy = obj->obj.cy;
	if (ft_intersect_ray_cylinder(inter, d, cy))
	{
		inter->is_hit = 1;
		inter->color = cy.color;
		inter->point = ft_add_vect(inter->origin, ft_mult_vect_s(inter->t, d));
		tmp = ft_sub_vect(inter->point, cy.cent);
		tmp2 = ft_mult_vect(cy.norm, tmp);
		inter->normal = ft_sub_vect(tmp, ft_mult_vect_s(tmp2, cy.norm));
		inter->normal = ft_normolize_vect(inter->normal);
		if (ft_mult_vect(d, inter->normal) > EPS)
			inter->normal = ft_mult_vect_s(-1, inter->normal);
	}
}

void	ft_closest_triangle(t_vect d, t_inter *inter, t_obj *obj)
{
	t_triangle tr;

	tr = obj->obj.tr;
	if (ft_intersect_ray_triangle(inter, d, tr))
	{
		inter->is_hit = 1;
		inter->color = tr.color;
		if (ft_mult_vect(d, inter->normal) > EPS)
			inter->normal = ft_mult_vect_s(-1, inter->normal);
		inter->normal = ft_normolize_vect(inter->normal);
	}
}
