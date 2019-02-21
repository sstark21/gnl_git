/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:28:14 by sstark            #+#    #+#             */
/*   Updated: 2019/02/21 18:33:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_reader(int fd)
{
	char	*buf;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (NULL);
	if ((read(fd, buf, BUFF_SIZE)) >= 0)
		return (ft_lstnew(buf, fd));
	free(buf);
	return (NULL);
}

t_list	*ft_lstsearch(int fd, t_list **lst)
{
	t_list	*lst1;
	char	buf[BUFF_SIZE + 1];

	lst1 = *lst;
	if (lst1 == NULL && fd >= 0)
		return (*lst = ft_reader(fd));
	while (lst1 != NULL)
	{
		if ((size_t)fd == lst1->content_size)
		{
			if (lst1->content == NULL)
			{
				buf[BUFF_SIZE] = '\0';
				if (read(fd, buf, BUFF_SIZE) > 0)
					lst1->content = ft_strjoin(buf, NULL);
				return (lst1);
			}
			else
				return (lst1);
		}
		if (lst1->next == NULL)
			return (lst1->next = ft_reader(fd));
		lst1 = lst1->next;
	}
	return (NULL);
}

int		get_next_line_part2(int rez, t_list *lst, char **line)
{
	char *tmp;

	if (rez == -1)
		return (-1);
	if (ft_strchr(lst->content, '\n') == NULL && rez < BUFF_SIZE)
	{
		*line = lst->content;
		lst->content = NULL;
		return (ft_strlen(*line) == 0 ? 0 : 1);
	}
	if (!(*line = ft_strsub(lst->content, 0,
			(ft_strchr(lst->content, '\n')) - (char *)lst->content)))
		return (-1);
	tmp = lst->content;
	if (ft_strchr(lst->content, '\n') != NULL)
	{
		if (!(lst->content = ft_strsub(tmp, ft_strchr(lst->content, '\n') -
		(char *)lst->content + 1, ft_strlen(ft_strchr(lst->content, '\n')
		+ 1))))
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
	while ((rez) == BUFF_SIZE && !(ft_strchr(lst->content, '\n')))
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
