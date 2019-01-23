/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:24:01 by sstark            #+#    #+#             */
/*   Updated: 2019/01/23 23:19:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_chek(char *buf)
{
	int i;

	i = 0;
	if (buf[i])
	{
		while (buf[i] != '\n' && buf[i])
			i++;
		printf("i = %d\n", i);
		return (buf[i] == '\n' ? i : 0);
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

	buf = ft_strnew(BUFF_SIZE);
	s = ft_strnew(BUFF_SIZE);
	read(fd, s, BUFF_SIZE);
	while ((rez = read(fd, buf, BUFF_SIZE)) > 0)
	{
		j = ft_chek(buf);
		//buf[rez] = '\0';
		printf("WHILE\n");
		printf("buf = %s\n", buf);
		printf("s = %s\n", s);
		if (j > 0)
		{
			s = ft_strnew(BUFF_SIZE);
			printf("IF1\n");
			printf("i = %d\n", j);
			s = ft_strsub(buf, 0, j);
			printf("s = %s\n", s);
			printf("buf = %s\n", buf);
		}
		if (j == 0)
		{
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
		}
		//printf("j = %d\n", j);
		//return (1);
	}
	return (0);
}
//	if (fd < 0 || line == NULL)
//		return (-1);
//	//printf("chr - %s\n", chr);
//	printf("bufNEW - %p\n", buf);
//	rez = 1;
//	if (!s || fd != fd1)
//	{
//		printf("IF\n");
//		s = ft_strnew(BUFF_SIZE);
//		fd1 = fd;
//		read(fd, s, BUFF_SIZE);
//		chr = ft_strnew(1);
//		chr = ft_strrchr(s, '\n');
//		printf("s - %s\n", s);
//		printf("chr - %s\n", chr);
//	}
//	while (rez > 0 && chr)
//	{
//		read(fd, s, BUFF_SIZE);
//		chr = ft_strchr(s, '\n');
//		printf("WHILE\n");
//		printf("s - %s\n", s);
//		buf = ft_strnew(BUFF_SIZE);
//		printf("bufSTRNEW - %p\n", buf);
//		rez = read(fd, buf, BUFF_SIZE);
//		printf("bufREZ - %p\n", buf);
//		tmp = ft_strjoin(s, buf);
//		free(s);
//		free(buf);
//		printf("bufFREE - %p\n", buf);
//		s = tmp;
//		chr = ft_strchr(s, '\n');
//		//printf("chr - %s\n", chr);
//		printf("rez - %d\n", rez);
//		//printf("s - %s\n", s);
//	}
//	printf("END\n");
//	printf("s - %s\n", s);
//	return (0);
//}

