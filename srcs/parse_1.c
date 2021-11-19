/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:06:55 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/02 00:12:23 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_set_cam(char *line, t_data *data)
{
	int		err;
	char	**str;
	t_vect	center;
	t_vect	normal;
	int		fov;

	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 3)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	err = ft_parse_vect(str[0], &center);
	err = ft_parse_norm(str[1], &normal);
	fov = ft_atoi(str[2]);
	if (fov <= 0 || fov >= 180 || !ft_is_int(fov))
		err = INVALID_MAP_ERR;
	ft_add_camera(&data->cams, ft_create_cam(center, normal, fov));
	free_text(str, ft_maslen(str));
	return (err);
}

int		ft_set_res(char *line, t_data *data)
{
	static int	is_set;
	char		**str;
	int			err;

	if (is_set)
		return (INVALID_MAP_ERR);
	err = 0;
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 2)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	data->win.w = ft_atof(str[0]);
	data->win.h = ft_atof(str[1]);
	if (data->win.w <= 0 || !ft_is_int(data->win.w) ||
			data->win.h <= 0 || !ft_is_int(data->win.h))
		err = INVALID_MAP_ERR;
	if (data->win.w > data->win.max_w)
		data->win.w = data->win.max_w;
	if (data->win.h > data->win.max_h)
		data->win.h = data->win.max_h;
	free_text(str, ft_maslen(str));
	is_set = 1;
	return (err);
}

int		ft_set_amb(char *line, t_data *data)
{
	int			err;
	static int	is_set;
	char		**str;
	double		intens;

	if (is_set)
		return (INVALID_MAP_ERR);
	str = ft_split_whitespace(line);
	if (ft_maslen(str) != 2)
	{
		free_text(str, ft_maslen(str));
		return (INVALID_MAP_ERR);
	}
	intens = ft_atof(str[0]);
	if (intens < 0.0 || intens > 1.0 || ft_isdigit(intens))
		err = INVALID_MAP_ERR;
	data->a.intens = intens;
	err = ft_parse_color(str[1], &data->a.color);
	free_text(str, ft_maslen(str));
	is_set = 1;
	return (err);
}

int		ft_parse_data(char *line, t_data *data, char *nl, char *nl2)
{
	int		err;

	err = 0;
	if (*line == 'R' && (*nl == ' ' || *nl == '\t'))
		err = ft_set_res(nl, data);
	else if (*line == 'A' && (*nl == ' ' || *nl == '\t'))
		err = ft_set_amb(nl, data);
	else if (*line == 'c' && (*nl == ' ' || *nl == '\t'))
		err = ft_set_cam(nl, data);
	else if (*line == 'l' && (*nl == ' ' || *nl == '\t'))
		err = ft_set_light(nl, data);
	else if (*line == 's' && *(nl) == 'p' && (*nl2 == ' ' || *nl2 == '\t'))
		err = ft_set_sphere(nl2, data);
	else if (*line == 'p' && *(nl) == 'l' && (*nl2 == ' ' || *nl2 == '\t'))
		err = ft_set_plane(nl2, data);
	else if (*line == 's' && *nl == 'q' && (*nl2 == ' ' || *nl2 == '\t'))
		err = ft_set_square(nl2, data);
	else if (*line == 'c' && *nl == 'y' && (*nl2 == ' ' || *nl2 == '\t'))
		err = ft_set_cylinder(nl2, data);
	else if (*line == 't' && *nl == 'r' && (*nl2 == ' ' || *nl2 == '\t'))
		err = ft_set_triangle(nl2, data);
	else if (*line != '\0')
		err = INVALID_MAP_ERR;
	return (err);
}

int		ft_parse(char *filename, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;
	int		err;

	err = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ft_print_error(FILENAME_ERR));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((err = ft_parse_data(line, data, line + 1, line + 2)) != 0)
		{
			ft_free_data(data);
			return (ft_print_error(err));
		}
		free(line);
	}
	ft_parse_data(line, data, line + 1, line + 2);
	free(line);
	if (ret < 0 || (close(fd)) == -1)
	{
		ft_free_data(data);
		return (ft_print_error(FILENAME_ERR));
	}
	return (0);
}
