/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:28:00 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:35:50 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	ft_create_cylinder(t_vect center, t_vect n, double dia, double h)
{
	t_cylinder cy;

	cy.cent = center;
	cy.norm = n;
	cy.r = dia / 2.0;
	cy.h = h;
	return (cy);
}

double		ft_trunc_cylinder(double t, t_vect d, t_cylinder cy, t_vect o)
{
	t_vect	cap;
	t_vect	ray;

	if (t < EPS)
		return (0);
	cap = ft_add_vect(cy.cent, ft_mult_vect_s(cy.h, cy.norm));
	ray = ft_add_vect(o, ft_mult_vect_s(t, d));
	if (ft_mult_vect(cy.norm, ft_sub_vect(ray, cy.cent)) < EPS)
		return (0);
	if (ft_mult_vect(cy.norm, ft_sub_vect(ray, cap)) > EPS)
		return (0);
	return (t);
}

int			ft_solve_cylinder(t_inter *in, t_vect d, t_cylinder cy)
{
	t_vect	t1;
	t_vect	t2;
	double	k1;
	double	k2;
	double	k3;

	t1 = ft_sub_vect(in->origin, cy.cent);
	t2 = ft_sub_vect(t1, ft_mult_vect_s(ft_mult_vect(t1, cy.norm), cy.norm));
	t1 = ft_sub_vect(d, ft_mult_vect_s(ft_mult_vect(d, cy.norm), cy.norm));
	k1 = ft_mult_vect(t1, t1);
	k2 = 2 * ft_mult_vect(t1, t2);
	k3 = ft_mult_vect(t2, t2) - cy.r * cy.r;
	in->t_1 = k2 * k2 - 4.0 * k1 * k3;
	if (in->t_1 < EPS)
		return (0);
	if (k2 > EPS)
		in->t_2 = (-k2 - sqrt(in->t_1)) / (2.0);
	else
		in->t_2 = (-k2 + sqrt(in->t_1)) / (2.0);
	in->t_1 = in->t_2 / k1;
	in->t_2 = k3 / in->t_2;
	if (in->t_1 < EPS && in->t_2 < EPS)
		return (0);
	return (1);
}

int			ft_intersect_ray_cylinder(t_inter *in, t_vect d, t_cylinder cy)
{
	double	t1;
	double	t2;
	double	t_min;

	if (!ft_solve_cylinder(in, d, cy))
		return (0);
	t1 = ft_trunc_cylinder(in->t_1, d, cy, in->origin);
	t2 = ft_trunc_cylinder(in->t_2, d, cy, in->origin);
	if ((t1 < EPS && t2 < EPS) || (t1 > in->t && t2 > in->t))
		return (0);
	if (t1 > EPS && t2 > EPS)
		t_min = ft_min(t1, t2);
	else if (t1 < EPS)
		t_min = t2;
	else if (t2 < EPS)
		t_min = t1;
	if (t_min < in->t)
		in->t = t_min;
	else
		return (0);
	return (1);
}
