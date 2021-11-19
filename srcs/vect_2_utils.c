/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 00:11:30 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/15 20:11:11 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	ft_zero_vect(void)
{
	t_vect	v;

	v.x = 0;
	v.y = 0;
	v.z = 0;
	return (v);
}

double	ft_mult_vect(t_vect v1, t_vect v2)
{
	double res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vect	ft_sub_vect(t_vect v1, t_vect v2)
{
	t_vect v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vect	ft_cross_v(t_vect v1, t_vect v2)
{
	t_vect	v3;

	v3.x = v1.y * v2.z - v1.z * v2.y;
	v3.y = v1.z * v2.x - v1.x * v2.z;
	v3.z = v1.x * v2.y - v1.y * v2.x;
	return (v3);
}
