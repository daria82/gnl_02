/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:35 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/21 21:21:33 by mstroeva         ###   ########.fr       */
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

char *ft_create(int i)
{
	char	*result;

	result = (char *)malloc(i * sizeof(char));
	if (result == NULL)
		return(NULL);
	*(result + (i - 1)) = '\0';
	return (result);
}

char *ft_full_free(char *tofree)
{
	free(tofree);
	return(NULL);
}

int ft_remtobuf(char *rem, char *buf)
{
	int x;

	ft_full_copy(buf, rem);
	//rem = ft_full_free(rem);
	x = ft_strlen(buf);
	return(x);
}

char *get_next_line(int fd)
{
	static char	*remain;
	int			byte_was_read;
	int			n_found;
	char		*buffer;
	char		*line;

	//printf("\n\n\tget next line pre-check and remain check STARTED:\n");
//===========================INITIAL CHECK + CREATE BUF AND LINE
	if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = ft_create(1)) || !(line = ft_create(1)))
		return (NULL);
//============================CREATE REMAIN, IF EXISTS >> SEND TO BUF AND ASSIGN BYTE WAS READ RESPECTIVELY
	if (remain)
	{
		//printf("\t-Information: remain contains: (%s)\n", remain);
		byte_was_read = ft_remtobuf(remain, buffer);
		remain = ft_full_free(remain);
		//if (remain == NULL)
			//printf("\tremain existed but now  = NULL\n");
	}
	else if (remain == NULL)
	{
		//printf("\t-Information: remain == 0\n");
		byte_was_read = read(fd, buffer, BUFFER_SIZE);	//load buffer with new text
		buffer[byte_was_read] = '\0';
		//if (remain == NULL)
			//printf("\tremain was and remained NULL\n");
	}
		//printf("\tget next line pre-check and remain check FINISHED (buffer = %s)\n\n\n", buffer);

//===========================START 
	while (byte_was_read > 0 && (n_found = search_n(buffer)) == -1)		// #2.THERE IS NO N IN THE BUFFER...
	{
		//printf("\tn_found=%d\n", n_found);
		line = ft_strjoin(line, buffer); 				//fill the line with buffer where n wasn't found
		//printf("line=(%s)\n", line);

		byte_was_read = read(fd, buffer, BUFFER_SIZE);
		n_found = search_n(buffer);		//search n in the renewed buffer
	}

	if (  (n_found = search_n(buffer)) >= 0  )		//#3. N IS FOUND!
	{
		//printf("N is found\n");
		line = ft_strjoin(line, ft_copy_head(buffer, (n_found + 1)));
		//printf("VERY FINAL line=(%s)\n", line);
		//printf("search symbol: (%c)\n", *(buffer + (n_found + 1)));
		remain = ft_strdup(buffer + (n_found + 1));

		//printf("VERY FINAL remain=(%s)\n", remain);
	}

	if (byte_was_read == 0) //almost eof >> returns what saved and next use will show eof. buffer is empty, freed, null
		{
			printf("nothing to read\n");
			buffer = ft_full_free(buffer);
			if (ft_strlen(line) == 0)
				line = ft_full_free(line);
			return(line);					// total eof
		}

		if (byte_was_read < 0)		// error in the file, just checking
		{
			printf("Error when reading the file\n");
			line = ft_full_free(line);
		}
		
	buffer = ft_full_free(buffer);

	return(line);
}
