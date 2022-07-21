/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line+.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:35 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/21 19:21:05 by mstroeva         ###   ########.fr       */
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
//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line.h get_next_line_utils.c main.c
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
	//copy from rem to buf including \0, returns equal to byte_read
	int x;

	if (!rem || !buf)
		return(-1);
	ft_full_copy(buf, rem);
//	rem = ft_full_free(rem);
	x = ft_strlen(buf);
	return(x);
}

char *ft_make_line(int fd, char *buffer, char *line, char *rem)
{

	int			byte_was_read;
	int			n_found;
	char		*tmp;


	//rem = (char *)malloc(sizeof(char));

	printf("\t\tline= (%s), strlen %ld\t", line, ft_strlen(line));
//	if (rem != NULL)
	//	printf("rem= (%s), strlen %ld\t", rem, ft_strlen(rem));
	printf("buffer= (%s), strlen %ld\n", buffer, ft_strlen(buffer));
	printf("\t3.continue make line\n");


	//printf("%d\n", search_n(buffer));
	
	if (rem != NULL)		//#1.SOMETHING FROM PREVIOUS USE? Y > SEND IN BUFFER; N > GO NEXT
	{
		printf("ONLY ONCE at start of the make line ft: because remain is not NUL copy rem to buf ");
		byte_was_read = ft_remtobuf(rem, buffer);
		rem = '\0';
		printf(">> buffer becomes = (%s)\n", buffer);

	}

	/*
	else if (remain[0] == '\0')
	{
		printf("remain0 is 0\n");
		byte_was_read = read(fd, buffer, BUFFER_SIZE);	//load buffer with new text
		buffer[byte_was_read] = '\0';
		printf("buffer after reading!! = %s\n", buffer);

	}
	*/

	printf("go to the while loop... >> ");
	while ((n_found = search_n(buffer)) == -1)
	{

		printf("becuse no N yet in buffer, send the buffer in line\n");
		line = ft_strjoin(line, buffer); 				//fill the line with buffer where n wasn't found
		printf("line after strjoin with buffer = (%s)\n", line);
		printf("fill the buffer with new data using read... ");
		byte_was_read = read(fd, buffer, BUFFER_SIZE);
		printf("now buffer= (%s), strlen %ld\n", buffer, ft_strlen(buffer));
		printf("search N using search_n ft... ");

		//n_found = search_n(buffer);		//search n in the renewed buffer
		printf("n_found = %d \n", n_found);

		if (byte_was_read == 0) //almost eof >> returns what saved and next use will show eof. buffer is empty, freed, null
		{
			printf("byte was read == 0\n");
			buffer = ft_full_free(buffer);
			if (ft_strlen(line) == 0)
				line = ft_full_free(line);
			return(line);					// total eof
		}

		if (byte_was_read < 0)		// error in the file, just checking
		{
			printf("error\n");
			line = ft_full_free(line);
			buffer = ft_full_free(buffer);
			return(NULL);
		}
	}
	printf("\tbecause n found in buffer, loop is over. \n");
	printf("\t\tline= (%s), strlen %ld\t", line, ft_strlen(line));
	//printf("rem= (%s), strlen %ld\t", rem, ft_strlen(rem));
	printf("buffer= (%s), strlen %ld\n", buffer, ft_strlen(buffer));

	if (  (n_found = search_n(buffer)) >= 0  )		//#3. N IS FOUND!
	{
		


		tmp = ft_create(n_found + 1);

		tmp = ft_copy_head(buffer, (n_found + 1));				//total copy
		line = ft_strjoin(line, tmp);
		printf("line AFTER TMP = %s\n", line);
		tmp = ft_full_free(tmp);
		// if (*(buffer + (n_found + 1)) != '\0')
		// {
		//	rem = ft_strdup((buffer + (n_found + 1)));
			// *(buffer + (n_found + 1));
				//	printf("FINAL remain = %s\n", remain);
				//	printf("FINAL rem = %s\n", rem);


		//}
	}

	return(line);
}




char *ft_make_line2(int fd, char *buffer, char **line, char *rem)
{
	int  byte_was_read;
	char *arr;
	char *brr;

	printf("mkl2: rem = (%s)\n", rem);
	if (rem != NULL)		//#1.SOMETHING FROM PREVIOUS USE? Y > SEND IN BUFFER; N > GO NEXT
	{
		printf("ONLY ONCE at start of the make line ft: because remain is not NUL copy rem to buf ");
		byte_was_read = ft_remtobuf(rem, buffer);
		rem = '\0';
		printf(">> buffer becomes = (%s)\n", buffer);

	}
	
	
	arr = "Hello";
	*line = arr;
	brr = "Bye";
	rem = brr;
	printf("mkl2: line = (%s)\n", *line);

	return(rem);
}


char *get_next_line(int fd)
{
	//static char	remain[9999];
	static char		*rem;
	char			*buffer;
	char			*line;
	int				byte_was_read;

	printf("\n\t1.gnl function starts... rem=%s\n", rem);
	if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = ft_create(BUFFER_SIZE + 1)) || !(line = ft_create(1)))
		return (NULL);

	rem = ft_create(BUFFER_SIZE + 1);

	if (rem != 0)
	{
			printf("something in rem => copy rem to buf, end of arr rem");
		byte_was_read = ft_remtobuf(rem, buffer);
		*rem = '\0';
			printf(">> buffer becomes = (%s)\n", buffer);
	}
			printf("nothing in rem? >> ");
	if (rem != 0)
		printf("nothing in rem!!! ");




		line = ft_full_free(line);
		buffer = ft_full_free(buffer);
		rem = ft_full_free(rem);


	return(NULL);
}
