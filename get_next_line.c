/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:24:01 by sstark            #+#    #+#             */
/*   Updated: 2019/01/22 19:19:19 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(const int fd, char **line)
{
	static char	*s;
	static int	fd1; //nahui static
	int			rez;
	char 		*buf;
	char 		*tmp;
	int			i;
	const char	*chr;

	if (fd < 0 || line == NULL)
		return (-1);
	s = ft_strnew(BUFF_SIZE);
	chr = ft_strchr(line, '\n');
	printf("s - %s\n", s);
	printf("line - %s\n", *line);
	printf("chr - %s\n", chr);
	if (!s || !fd)
	{
		read(fd, s, BUFF_SIZE);
		fd1 = fd;
		printf("point2\n");
	}
	while ((rez = read(fd, buf, BUFF_SIZE)) && !s)
	{
		buf = ft_strnew(BUFF_SIZE);
		tmp = ft_strjoin(s, buf);
		free(s);
		free(buf);
		s = tmp;
		printf("s - %s\n", s);
	}
	printf("s - %s\n", buf);
	return (0);
}