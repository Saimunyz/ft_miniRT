/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:54:15 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/01 23:42:41 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "stdlib.h"
# include "unistd.h"
# define BUFFER_SIZE 50

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup_gnl(const char *s1, size_t len);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		get_next_line(int fd, char **line);

#endif
