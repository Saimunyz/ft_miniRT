/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 01:41:17 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/02 00:26:51 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect		ft_get_ray(t_win win, t_camera *cam, double x, double y)
{
	t_vect	ray;
	double	fov;
	double	ratio;

	ratio = (double)win.w / (double)win.h;
	fov = tan(cam->fov / 2.0 * PI / 180.0);
	ray.x = ((2 * ((x + 0.5) / win.w)) - 1) * ratio * fov;
	ray.y = 1 - 2 * ((y + 0.5) / win.h) * fov;
	ray.z = 1;
	ray = ft_cam_direction(ray, cam->normal);
	return (ray);
}
