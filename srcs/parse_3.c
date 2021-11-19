/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:45:07 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/02 00:33:38 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_parse_color(char *line, int *color)
{
	int		r;
	int		g;
	int		b;
	char	**str;
	int		err;

	err = 0;
	str = ft_split(line, ',');
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	r = ft_atoi(str[0]);
	if (r < 0 || r > 255 || !ft_is_int(r))
		err = INVALID_MAP_ERR;
	g = ft_atoi(str[1]);
	if (g < 0 || g > 255 || !ft_is_int(g))
		err = INVALID_MAP_ERR;
	b = ft_atoi(str[2]);
	if (b < 0 || b > 255 || !ft_is_int(b))
		err = INVALID_MAP_ERR;
	*color = create_trgb(255, r, g, b);
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_parse_vect(char *line, t_vect *vect)
{
	char	**str;
	int		err;

	err = 0;
	str = ft_split(line, ',');
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	vect->x = ft_atof(str[0]);
	vect->y = ft_atof(str[1]);
	vect->z = ft_atof(str[2]);
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_parse_norm(char *line, t_vect *norm)
{
	char	**str;
	int		err;

	err = 0;
	str = ft_split(line, ',');
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	norm->x = ft_atof(str[0]);
	if (norm->x < -1.0 || norm->x > 1.0)
		err = INVALID_MAP_ERR;
	norm->y = ft_atof(str[1]);
	if (norm->y < -1.0 || norm->y > 1.0)
		err = INVALID_MAP_ERR;
	norm->z = ft_atof(str[2]);
	if (norm->z < -1.0 || norm->z > 1.0)
		err = INVALID_MAP_ERR;
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_set_triangle(char *line, t_data *data)
{
	int			err;
	char		**str;
	t_triangle	tr;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 4)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &tr.p1);
	err = ft_parse_vect(str[1], &tr.p2);
	err = ft_parse_vect(str[2], &tr.p3);
	err = ft_parse_color(str[3], &tr.color);
	ft_add_obj(&data->obj, ft_new_obj(TRIANGLE, (void*)&tr));
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_check_data(t_data *data)
{
	int	err;

	err = 0;
	if (data->cams == NULL)
		err = ft_print_error(INCOMPLITE_MAP_ERR);
	else if (data->win.h == 0 || data->win.w == 0)
		err = ft_print_error(INCOMPLITE_MAP_ERR);
	else if (data->a.intens == 0)
		err = ft_print_error(INCOMPLITE_MAP_ERR);
	if (err != 0)
		ft_free_data(data);
	return (err);
}
