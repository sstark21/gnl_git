/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:28:14 by sstark            #+#    #+#             */
/*   Updated: 2019/02/12 17:26:40 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_list			*lst1;

	lst1 = *lst;
	if (lst1 == NULL && fd >= 0)
	{
		if (!(buf = ft_strnew(BUFF_SIZE)))
			return (NULL);
		read(fd, buf, BUFF_SIZE);
		return (*lst = ft_lstnew(buf, fd));
	}
	while (lst1 != NULL)
	{
		if ((size_t)fd == lst1->content_size)
		{
			if (lst1->content == NULL)
			{
				if (!(buf = ft_strnew(BUFF_SIZE)))
					return (NULL);
				else if ((read(fd, buf, BUFF_SIZE)) > 0)
					return (lst1->next = ft_lstnew(buf, fd));
				else
					ft_del_from(lst, lst1, NULL);
			}
			else
				return (lst1);
		}
		if (lst1->next == NULL)
		{
			if (!(buf = ft_strnew(BUFF_SIZE)))
				return (NULL);
			if ((read(fd, buf, BUFF_SIZE)) != -1)
				return (lst1->next = ft_lstnew(buf, fd));
		}
		lst1 = lst1->next;
	}
	return (NULL);
}

int		get_next_line_part2(int rez, t_list *lst, char **line)
{
	char *tmp;

	if (rez == -1)
		return (-1);
	if (ft_chek(lst->content) == 0 || rez == 0)
	{
		*line = lst->content;
		lst->content = NULL;
		return (ft_strlen(*line) == 0 ? 0 : 1);
	}
	if (!(*line = ft_strsub(lst->content, 0, ft_chek(lst->content) - 1)))
		return (-1);
	tmp = lst->content;
	if (ft_strlen(&(tmp[ft_chek(lst->content)])) > 0)
	{
		if (!(lst->content = ft_strsub(tmp, ft_chek(lst->content),
				ft_strlen(&(tmp[ft_chek(lst->content)])))))
			return (-1);
	}
	else
		lst->content = ft_strnew(0);
	free(tmp);
	return (1);
}

int		chek_mistake(int fd, char **line, t_list **f, t_list **lst)
{
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*lst = ft_lstsearch(fd, f)))
		return (-1);
	if ((*lst)->content == NULL)
	{
		*line = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int				rez;
	char			*tmp;
	static t_list	*f;
	char			*buf;
	t_list			*lst;

	rez = BUFF_SIZE;
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (chek_mistake(fd, line, &f, &lst) != 1)
		return (chek_mistake(fd, line, &f, &lst));
	while ((rez) == BUFF_SIZE && !(ft_chek(lst->content)))
	{
		rez = read(lst->content_size, buf, BUFF_SIZE);
		if (rez < BUFF_SIZE)
			buf[rez] = '\0';
		tmp = lst->content;
		if (!(lst->content = ft_strjoin(lst->content, buf)))
			return (-1);
		free(tmp);
	}
	free(buf);
	return (get_next_line_part2(rez, lst, line));
}
