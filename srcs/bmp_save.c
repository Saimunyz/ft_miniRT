/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 01:10:11 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 21:08:54 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_write_byte(int fd, unsigned int byte, size_t size)
{
	int ret;

	ret = write(fd, &byte, size);
	return (ret);
}

static int	ft_write_header(int fd, t_data *data)
{
	unsigned int	f_size;

	f_size = 54 + data->win.h * data->win.w * 4;
	ft_write_byte(fd, 0x42, 1);
	ft_write_byte(fd, 0x4D, 1);
	ft_write_byte(fd, f_size, 4);
	ft_write_byte(fd, 0x00, 4);
	ft_write_byte(fd, 0x36, 4);
	ft_write_byte(fd, 0x28, 4);
	ft_write_byte(fd, data->win.w, 4);
	ft_write_byte(fd, data->win.h, 4);
	ft_write_byte(fd, 0x01, 2);
	ft_write_byte(fd, 0x20, 2);
	ft_write_byte(fd, 0x00, 4);
	ft_write_byte(fd, data->win.h * data->win.w * 4, 4);
	ft_write_byte(fd, 0x00, 4);
	ft_write_byte(fd, 0x00, 4);
	ft_write_byte(fd, 0x00, 4);
	ft_write_byte(fd, 0x00, 4);
	return (0);
}

int			ft_save_bmp(t_data *data)
{
	int		fd;
	void	*addr;
	int		line_size;
	int		y;

	if ((fd = open("miniRT.bmp", O_WRONLY | O_CREAT | O_TRUNC)) == -1)
		return (ft_print_error(BMP_ERR));
	addr = data->mlx.addr;
	line_size = data->win.w * data->mlx.bpp / 8;
	y = data->win.h;
	ft_write_header(fd, data);
	while (y--)
		write(fd, addr + line_size + y * data->mlx.ll, line_size);
	if ((close(fd) == -1))
	{
		ft_free_data(data);
		return (ft_print_error(BMP_ERR));
	}
	return (0);
}
