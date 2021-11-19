/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:35:43 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/02 00:26:43 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ft_min(double n1, double n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

double		ft_max(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

double		ft_abs(double n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

t_inter		ft_init_inter(t_vect origin)
{
	t_inter		i;

	i.color = 0;
	i.is_hit = 0;
	i.normal = ft_zero_vect();
	i.origin = origin;
	i.point = ft_zero_vect();
	i.t = INF;
	i.t_1 = INF;
	i.t_2 = INF;
	return (i);
}

void		ft_free_data(t_data *data)
{
	ft_clear_camera(&data->cam_begin);
	ft_clear_light(&data->l);
	ft_clear_obj(&data->obj);
	data->cam_begin = NULL;
	data->cams = NULL;
	data->l = NULL;
	data->obj = NULL;
}
