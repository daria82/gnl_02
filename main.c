/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:41:55 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/21 23:49:31 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	if (fd < 0)
	{
 		printf("Error. Wrong file descriptor!");
		return(0);
	}
	printf("\tfd: (%d)\n", fd);
	line = (char *)malloc(1 * sizeof(char));
	printf("\033[1;36m \n>>>>>go to get next line function:\n\033[0m");
	//		line = get_next_line(fd);
	//				line = get_next_line(fd);
	int i = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		//printf("use of gnl/line %d: \033[1;35m%s\033[0m", i, line);
		printf("\033[1;35m%s\033[0m", line);

		i++;
	}
	
	free(line);
	close(fd);
	return(0);
}
