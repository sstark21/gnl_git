/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:28:14 by sstark            #+#    #+#             */
/*   Updated: 2019/02/06 23:10:39 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int		ft_chek(char *buf)
{
	int				i;

	i = 1;
	if (buf)
	{
		while (buf[i - 1] != '\n' && buf[i - 1])
			i++;
		return (buf[i - 1] == '\n' ? i : 0);
	}
	return (0);
}

t_list	*ft_lstsearch(int fd, t_list **lst)
{
	char			*buf;
	int				x;
	t_list			*lst1;

	lst1 = *lst;
	if (lst1 == NULL && fd >= 0)
	{
		if (!(buf = ft_strnew(BUFF_SIZE)))
			return (NULL);
		x = read(fd, buf, BUFF_SIZE);
		return (*lst = ft_lstnew(buf, fd));
	}
	else
	{
		while (lst1 != NULL)
		{
			if ((size_t)fd == lst1->content_size)
				return (lst1);
			if (lst1->next == NULL)
			{
				if (!(buf = ft_strnew(BUFF_SIZE)))
					return (NULL);
				if ((x = read(fd, buf, BUFF_SIZE)) != -1)
					return (lst1->next = ft_lstnew(buf, fd));
			}
			lst1 = lst1->next;
		}
	}
	return (NULL);
}

int		get_next_line(const int fd, char **line)
{
	int				rez;
	char			*tmp;
	static t_list	*f;
	char			*buf;
	t_list			*lst;

	if (fd < 0 || line == NULL)
		return (-1);
	rez = BUFF_SIZE;
	if (!(lst = ft_lstsearch(fd, &f)))
		return (-1);
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (lst->content == NULL)
	{	*line = NULL;
		return (0);
	}
	while ((rez) == BUFF_SIZE && !(ft_chek(lst->content)))
	{
		rez = read(lst->content_size, buf, BUFF_SIZE);
		if (rez < BUFF_SIZE)
			buf[rez] = '\0';
		//printf("buf :%s rez :%d ", buf, rez);
		tmp = lst->content;
		if (!(lst->content = ft_strjoin(lst->content, buf)))
			return (-1);
		free(tmp);
	}
	free(buf);
	if (rez == -1)
		return (-1);
	if (ft_chek(lst->content) == 0 || rez == 0)
	{
		//printf("rez - %d", rez);
		*line = lst->content;
		lst->content = NULL;
		return (ft_strlen(*line) == 0 ? 0 : 1);
	}
	else
	{
		if (!(*line = ft_strsub(lst->content, 0, ft_chek(lst->content) - 1)))
			return (-1);
		tmp = lst->content;
//		if (!(lst->content = ft_strsub(tmp, ft_chek(lst->content),
//				ft_strlen(&(tmp[ft_chek(lst->content)])))))
//			return (-1);
		if (ft_strlen(&(tmp[ft_chek(lst->content)])) > 0)
		{
			//printf("i - %zu\n", ft_strlen(&(tmp[ft_chek(lst->content)])));
			if (!(lst->content = ft_strsub(tmp, ft_chek(lst->content),
										   ft_strlen(&(tmp[ft_chek(lst->content)])))))
				return (-1);
		}
		else
			lst->content = ft_strnew(0);
		free(tmp);
		return (1);
	}
}
