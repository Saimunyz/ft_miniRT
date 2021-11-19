/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:53:05 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:15:09 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_buff(char *buff, char **line)
{
	size_t	len;
	char	*str;
	char	*tmp;

	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	str = ft_strdup_gnl(buff, len);
	tmp = ft_strjoin(*line, str);
	free(*line);
	free(str);
	*line = tmp;
	if (buff[len] == '\n')
		return (ft_strdup_gnl(buff + len + 1, ft_strlen(buff + len + 1)));
	return (NULL);
}

int		check_rem(char **rem, char **tmp)
{
	char	*tmp1;

	if (*rem && *tmp)
	{
		tmp1 = save_buff(*rem, tmp);
		free(*rem);
		*rem = tmp1;
		if (*rem && *tmp)
			return (1);
	}
	return (0);
}

int		set_result(int ret, char *rem)
{
	free(rem);
	if (ret == 0)
		return (0);
	else
		return (-1);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*rem;
	char			*tmp;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	tmp = ft_strdup_gnl("", 0);
	if (check_rem(&rem, &tmp))
	{
		*line = tmp;
		return (1);
	}
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0 && tmp)
	{
		buff[ret] = '\0';
		rem = save_buff(buff, &tmp);
		if (rem && tmp)
		{
			*line = tmp;
			return (1);
		}
	}
	*line = tmp;
	return (set_result(ret, rem));
}
