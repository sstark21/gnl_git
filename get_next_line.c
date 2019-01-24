/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:24:01 by sstark            #+#    #+#             */
/*   Updated: 2019/01/24 18:41:19 by sstark           ###   ########.fr       */
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
			printf("C = %c\n", buf[i - 1]);
		}
		return (buf[i - 1] == '\n' ? i : 0);
	}
	return (0);
}


int	get_next_line(const int fd, char **line)
{
	static char *s;
	static int fd1; //nahui static
	int rez;
	char *buf;
	char *tmp;
	int j;
	const char *chr;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!s || fd != fd1)
	{
		fd1 = fd;
		buf = ft_strnew(BUFF_SIZE);
		s = ft_strnew(BUFF_SIZE);
		rez = read(fd, s, BUFF_SIZE);
	}
	while ((rez) > 0 && !(j = ft_chek(buf)))
	{
/*		printf("WHILE\n");
		printf("buf = %s\n", buf);
		printf("s = %s\n", s);
		if (j > 0)
		{

			s = ft_strnew(BUFF_SIZE);
			printf("IF1\n");
			printf("i = %d\n", j);
			s = ft_strjoin(s, ft_strsub(buf, 0, j));
			buf[j] = '\0';
			printf("s = %s\n", s);
			printf("buf = %s\n", buf);
		}*/
		printf("J = %d\n", j);
		rez = read(fd, buf, BUFF_SIZE);
		//s = ft_strnew(BUFF_SIZE);
		printf("IF2\n");
		printf("s = %s\n", s);
		printf("buf = %s\n", buf);
		//printf("%p\n%p\n", s, buf);
		tmp = ft_strjoin(s, buf);
		//puts("debug0");
		printf("tmp = %s\n", tmp);
		//free(buf);
		free(s);
		s = tmp;
		printf("s = %s\n", s);
		printf("buf = %s\n", buf);
		//printf("j = %d\n", j);
		//return (1);
	}
	if (j == 0 && rez == 0)
	{
		printf("IF3\n");
		*line = s;
		s = ft_strnew(0);
		return (1);
	}
	else
	{
		printf("ELSE\n");
		j = ft_chek(s);
		*line = ft_strsub(s, 0, j - 1);
		tmp = s;
		s = ft_strdup(s + j - 1);
		free (tmp);
	}
	return (0);
}
/*	if (fd < 0 || line == NULL)
		return (-1);
	//printf("chr - %s\n", chr);
	printf("bufNEW - %p\n", buf);
	rez = 1;
	if (!s || fd != fd1)
	{
		printf("IF\n");
		s = ft_strnew(BUFF_SIZE);
		fd1 = fd;
		read(fd, s, BUFF_SIZE);
		chr = ft_strnew(1);
		chr = ft_strrchr(s, '\n');
		printf("s - %s\n", s);
		printf("chr - %s\n", chr);
	}
	while (rez > 0 && chr)
	{
		read(fd, s, BUFF_SIZE);
		chr = ft_strchr(s, '\n');
		printf("WHILE\n");
		printf("s - %s\n", s);
		buf = ft_strnew(BUFF_SIZE);
		printf("bufSTRNEW - %p\n", buf);
		rez = read(fd, buf, BUFF_SIZE);
		printf("bufREZ - %p\n", buf);
		tmp = ft_strjoin(s, buf);
		free(s);
		free(buf);
		printf("bufFREE - %p\n", buf);
		s = tmp;
		chr = ft_strchr(s, '\n');
		//printf("chr - %s\n", chr);
		printf("rez - %d\n", rez);
		//printf("s - %s\n", s);
	}
	printf("END\n");
	printf("s - %s\n", s);
	return (0);
}*/

