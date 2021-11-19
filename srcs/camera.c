/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:28:44 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/26 23:59:31 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*ft_create_cam(t_vect center, t_vect normal, double fov)
{
	t_camera *o;

	o = malloc(sizeof(t_camera));
	if (o)
	{
		o->center.x = center.x;
		o->center.y = center.y;
		o->center.z = center.z;
		o->normal.x = normal.x;
		o->normal.y = normal.y;
		o->normal.z = normal.z;
		o->fov = fov;
		o->next = NULL;
	}
	return (o);
}

void		ft_add_camera(t_camera **lst, t_camera *new)
{
	t_camera	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			ft_lst_camera_size(t_camera *cam)
{
	size_t	counter;

	counter = 0;
	if (!cam)
		return (0);
	while (cam)
	{
		cam = cam->next;
		counter++;
	}
	return (counter);
}

void		ft_clear_camera(t_camera **cam)
{
	t_camera	*tmp;
	t_camera	*free_list;

	tmp = *cam;
	while (tmp && tmp->next)
	{
		free_list = tmp;
		tmp = tmp->next;
		free(free_list);
	}
	free(tmp);
	*cam = NULL;
}

t_vect		ft_cam_direction(t_vect o, t_vect normal)
{
	t_vect		up_vect;
	t_vect		right;
	t_vect		up;
	t_vect		ray;

	up_vect = ft_create_vect(0, 1, 0);
	if (normal.y == 1)
		right = ft_create_vect(1, 0, 0);
	else if (normal.y == -1)
		right = ft_create_vect(-1, 0, 0);
	else
		right = ft_cross_v(up_vect, ft_normolize_vect(normal));
	up = ft_normolize_vect(ft_cross_v(normal, right));
	ray.x = o.x * right.x + o.y * up.x + o.z * normal.x;
	ray.y = o.x * right.y + o.y * up.y + o.z * normal.y;
	ray.z = o.x * right.z + o.y * up.z + o.z * normal.z;
	return (ft_normolize_vect(ray));
}
