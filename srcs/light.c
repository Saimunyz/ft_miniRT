/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 13:45:57 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/21 02:22:12 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*ft_create_light(double intens, t_vect p, int color)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (l)
	{
		l->color = color;
		l->i = intens;
		l->p = p;
		l->next = NULL;
	}
	return (l);
}

t_amb	ft_create_ambient(double intens, int color)
{
	t_amb	a;

	a.color = color;
	a.intens = intens;
	return (a);
}

void	ft_add_light(t_light **lst, t_light *new)
{
	t_light	*tmp;

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

void	ft_clear_light(t_light **l)
{
	t_light	*tmp;
	t_light	*free_list;

	tmp = *l;
	while (tmp && tmp->next)
	{
		free_list = tmp;
		tmp = tmp->next;
		free(free_list);
	}
	free(tmp);
	*l = NULL;
}

int		ft_lst_light_size(t_light *l)
{
	size_t	counter;

	counter = 0;
	if (!l)
		return (0);
	while (l)
	{
		l = l->next;
		counter++;
	}
	return (counter);
}
