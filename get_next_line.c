/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:24:01 by sstark            #+#    #+#             */
/*   Updated: 2019/01/27 15:13:49 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_chek(char *buf)
{
	int i;

	i = 1;
	if (buf)
	{
		while (buf[i -1] != '\n' && buf[i - 1]) {
			i++;
		}
		return (buf[i - 1] == '\n' ? i : 0);
	}
	return (0);
}

//t_list	*ft_search(const int fd)
//{
//
//}


int	get_next_line(const int fd, char **line)
{
	static char	*s;
	static int	fd1;
	int			rez;
	char		*buf;
	char		*tmp;
	int			j;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!s || fd != fd1)
	{
		fd1 = fd;
		s = ft_strnew(BUFF_SIZE);
		rez = read(fd, s, BUFF_SIZE);
		buf = ft_strdup(s);
	}
	else
		buf = ft_strnew(BUFF_SIZE);
	while ((rez) > 0 && !(j = ft_chek(buf)))
	{
		if (j > 0)
		{
			s = ft_strnew(BUFF_SIZE);
			s = ft_strjoin(s, ft_strsub(buf, 0, j));
			buf[j] = '\0';
		}
		rez = read(fd, buf, BUFF_SIZE);
		tmp = ft_strjoin(s, buf);
		free(s);
		s = tmp;
	}
	free(buf);
	if (j == 0 && rez == 0)
	{
		*line = s;
		s = ft_strnew(0);
		return (1);
	}
	else
	{
		j = ft_chek(s);
		*line = ft_strsub(s, 0, j - 1);
		tmp = s;
		s = ft_strdup(s + j);
		free (tmp);
	}
	return (0);
}
