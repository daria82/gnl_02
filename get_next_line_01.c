/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:35 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/12 15:14:33 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function name 	get_next_line
Prototype		char *get_next_line(int fd);
Turn in files	get_next_line.c, get_next_line_utils.c, get_next_line.h
Parameters fd:	The file descriptor to read from
Return value	Read line:		correct behavior
				NULL: there is nothing else to read, or an error occurred
External functs.read, malloc, free
Description		Write a function that returns a line read from a file descriptor

//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c


*/
#include "get_next_line.h"
# include <stdio.h> // temp! delete before finishing

char *get_next_line(int fd)
{
	static char	*remain;
	int			byte_was_read;
	int			n_found;
	char		*buffer;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)									//if there are initial errors
		return (NULL);

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));		//allocate  a buffer
	if (NULL == buffer)	
		return (NULL);

	line = (char *)malloc(1 * sizeof(char));
	*line = '\0';
	n_found = -1;

	if (remain != NULL)		//#1.SOMETHING FROM PREVIOUS USE? Y > SEND IN BUFFER; N > GO NEXT
	{
		//printf("SOMETHING REMAINED FROM LAST TIME! (%s)\n", remain);
		ft_full_copy(buffer, remain);
		free(remain);
		remain = NULL;
		n_found = search_n(buffer);
	}

	while (n_found == -1)		// #2.THERE IS NO N IN THE BUFFER...
	{
		line = ft_strjoin(line, buffer); 				//fill the line with buffer where n wasn't found
		byte_was_read = read(fd, buffer, BUFFER_SIZE);	//load buffer with new text
		buffer[byte_was_read] = '\0';

		if (byte_was_read == 0) //almost eof >> returns what saved and next use will show eof. buffer is empty, freed, null
		{
			free(buffer);
			buffer = NULL;
			if (ft_strlen(line) == 0)
			{
				free(line);
				line = NULL;
			}
			return(line);					// total eof
		}

		if (byte_was_read < 0)		// error in the file, just checking
		{
			free(buffer);
			free(line);
			return(NULL);
		}
		
		n_found = search_n(buffer);		//search n in the renewed buffer
	}

	if (n_found >= 0)		//#3. N IS FOUND!
	{
		//printf("N is found. Buffer is divided on line and remain\n");
		tmp = (char *)malloc((n_found + 1)*sizeof(char));		//if n is the last it will be just a copy of buffer
		tmp = ft_copy_head(buffer, (n_found + 1));				//total copy

		line = ft_strjoin(line, tmp);
		free(tmp);
		tmp = NULL;

		if (*(buffer + (n_found + 1)) != '\0')
		{
			//printf("N happened at the end of the line, remain LEFT NULLified.\n");
			remain = (char *)malloc(1 * sizeof(char));
			remain = ft_strjoin(remain, (buffer + (n_found + 1)));
			printf("line=(%s)", line);
			printf("remain=(%s)", remain);
		}
	}
	free(buffer);
	buffer = NULL;
	return(line);
}
