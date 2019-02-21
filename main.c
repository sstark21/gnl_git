/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksnow-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:15:15 by ksnow-be          #+#    #+#             */
/*   Updated: 2019/02/21 18:32:52 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
int	main(int argc, char **argv)
{
	int		fd;
    char	*line;
	int re;

	if (argc > 1)
    {
        fd=open(argv[1], O_RDONLY);
    	while ((re = get_next_line(fd, &line)) == 1)
		{
			printf("\033[34m%s\n", line);
			printf("%d\n",re);
			free(line);
		}
		printf("%d\n",re);
	}
	return (0);
}
