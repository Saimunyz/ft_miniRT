/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 00:25:57 by swagstaf          #+#    #+#             */
/*   Updated: 2021/03/21 11:37:33 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*ft_new_obj(enum e_obj type, void *data)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (obj)
	{
		obj->type = type;
		if (obj->type == PLANE)
			obj->obj.pl = *((t_plane*)data);
		else if (obj->type == SPHERE)
			obj->obj.sp = *((t_sphere*)data);
		else if (obj->type == SQUARE)
			obj->obj.sq = *((t_square*)data);
		else if (obj->type == TRIANGLE)
			obj->obj.tr = *((t_triangle*)data);
		else if (obj->type == CYLINDER)
			obj->obj.cy = *((t_cylinder*)data);
		obj->next = NULL;
	}
	return (obj);
}

void	ft_add_obj(t_obj **lst, t_obj *new)
{
	t_obj	*tmp;

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

void	ft_clear_obj(t_obj **obj)
{
	t_obj	*tmp;
	t_obj	*free_list;

	tmp = *obj;
	while (tmp && tmp->next)
	{
		free_list = tmp;
		tmp = tmp->next;
		free(free_list);
	}
	free(tmp);
	*obj = NULL;
}

int		ft_lst_obj_size(t_obj *obj)
{
	size_t	counter;

	counter = 0;
	if (!obj)
		return (0);
	while (obj)
	{
		obj = obj->next;
		counter++;
	}
	return (counter);
}
