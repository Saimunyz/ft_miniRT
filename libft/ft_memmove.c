/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:13:22 by swagstaf          #+#    #+#             */
/*   Updated: 2020/10/30 14:55:05 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = len - 1;
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (s >= d)
		ft_memcpy(d, s, len);
	else
	{
		while (i + 1)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (d);
}
