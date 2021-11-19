/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:41:23 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:41:16 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_set_light(char *line, t_data *data)
{
	int		err;
	char	**str;
	t_vect	center;
	double	intens;
	int		color;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &center);
	intens = ft_atof(str[1]);
	if (intens < 0.0 || intens > 1.0 || ft_isdigit(intens))
		err = INVALID_MAP_ERR;
	err = ft_parse_color(str[2], &color);
	ft_add_light(&data->l, ft_create_light(intens, center, color));
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_set_sphere(char *line, t_data *data)
{
	int			err;
	char		**str;
	double		diam;
	t_sphere	sp;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &sp.center);
	diam = ft_atof(str[1]);
	if (diam <= 0.0)
		err = INVALID_MAP_ERR;
	err = ft_parse_color(str[2], &sp.c);
	sp.r = diam / 2.0;
	ft_add_obj(&data->obj, ft_new_obj(SPHERE, (void*)&sp));
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_set_plane(char *line, t_data *data)
{
	int			err;
	char		**str;
	t_plane		pl;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &pl.center);
	err = ft_parse_vect(str[1], &pl.normal);
	err = ft_parse_color(str[2], &pl.color);
	ft_add_obj(&data->obj, ft_new_obj(PLANE, (void*)&pl));
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_set_square(char *line, t_data *data)
{
	int			err;
	char		**str;
	double		side_size;
	t_square	sq;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 4)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &sq.center);
	err = ft_parse_vect(str[1], &sq.normal);
	side_size = ft_atof(str[2]);
	if (side_size <= 0.0)
		err = INVALID_MAP_ERR;
	err = ft_parse_color(str[3], &sq.color);
	sq.h = side_size;
	ft_add_obj(&data->obj, ft_new_obj(SQUARE, (void*)&sq));
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_set_cylinder(char *line, t_data *data)
{
	int			err;
	char		**str;
	double		diam;
	t_cylinder	cy;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 5)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &cy.cent);
	err = ft_parse_vect(str[1], &cy.norm);
	diam = ft_atof(str[2]);
	if (diam <= 0.0)
		err = INVALID_MAP_ERR;
	cy.h = ft_atof(str[3]);
	if (cy.h <= 0.0)
		err = INVALID_MAP_ERR;
	err = ft_parse_color(str[4], &cy.color);
	cy.r = diam / 2.0;
	ft_add_obj(&data->obj, ft_new_obj(CYLINDER, (void*)&cy));
	free_text(str, ft_maslen(str));
	return (err);
}
