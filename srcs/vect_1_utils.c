/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_1_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:35:51 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/21 02:27:14 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_len_v(t_vect v)
{
	double length;

	length = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (length);
}

t_vect	ft_normolize_vect(t_vect v)
{
	double length;

	length = ft_len_v(v);
	if (length != 1 && length != 0)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return (v);
}

t_vect	ft_add_vect(t_vect v1, t_vect v2)
{
	t_vect v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vect	ft_mult_vect_s(double scalar, t_vect v)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return (v);
}

t_vect	ft_create_vect(double x, double y, double z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
