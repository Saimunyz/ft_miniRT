/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:26:06 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:39:03 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter		ft_calc_t(t_vect cam, t_vect d, t_obj *object)
{
	t_inter	inter;
	t_obj	*obj;

	inter = ft_init_inter(cam);
	obj = object;
	while (obj)
	{
		if (obj->type == PLANE)
			ft_closest_plane(d, &inter, obj);
		else if (obj->type == SPHERE)
			ft_closest_sphere(d, &inter, obj);
		else if (obj->type == SQUARE)
			ft_closest_square(d, &inter, obj);
		else if (obj->type == TRIANGLE)
			ft_closest_triangle(d, &inter, obj);
		else if (obj->type == CYLINDER)
			ft_closest_cylinder(d, &inter, obj);
		obj = obj->next;
	}
	return (inter);
}

int			ft_shadow(t_vect ray, t_inter inter, t_obj *obj)
{
	inter.normal = ft_mult_vect_s(EPS, inter.normal);
	inter.origin = ft_add_vect(inter.point, inter.normal);
	inter = ft_calc_t(inter.origin, ft_normolize_vect(ray), obj);
	if (inter.is_hit == 1 && (inter.t < ft_len_v(ray)))
		return (1);
	return (0);
}

double		ft_comp_diffuse(t_light *light, t_vect n, t_vect l)
{
	double	n_dot_l;
	double	diffuse;

	n_dot_l = ft_mult_vect(n, l);
	diffuse = 0.0;
	if (n_dot_l > EPS)
		diffuse = light->i * n_dot_l / (ft_len_v(n) * ft_len_v(l));
	return (diffuse);
}

int			ft_comp_light(t_data *f, t_light *light, t_inter inter)
{
	double	intens;
	t_vect	l;
	int		color;
	int		light_color;

	color = 0x00000000;
	while (light)
	{
		l = ft_sub_vect(light->p, inter.point);
		if (ft_shadow(l, inter, f->obj))
			intens = 0;
		else
			intens = ft_comp_diffuse(light, inter.normal, l);
		light_color = ft_mult_color_s(light->color, intens);
		light_color = ft_mult_color(inter.color, light_color);
		color = ft_add_color(color, light_color);
		light = light->next;
	}
	light_color = ft_mult_color_s(f->a.color, f->a.intens);
	light_color = ft_mult_color(inter.color, light_color);
	color = ft_add_color(color, light_color);
	return (color);
}

int			ft_trace_ray(t_data *data, t_vect ray)
{
	t_inter		inter;
	int			color;

	inter = ft_calc_t(data->cams->center, ray, data->obj);
	if (inter.is_hit == 0)
		return (create_trgb(255, 0, 0, 0));
	color = ft_comp_light(data, data->l, inter);
	return (color);
}
