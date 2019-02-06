/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:28:22 by sstark            #+#    #+#             */
/*   Updated: 2019/02/06 22:48:47 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_LIST
# define GET_NEXT_LINE_LIST

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 5

int get_next_line(const int fd, char **line);

#endif
