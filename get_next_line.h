/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:37:17 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/12 15:11:58 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // temp! delete before finishing
/*
#include <unistd.h> //write and read
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> // open
//#include "libft/libft.h"
#include <ctype.h>
#include <string.h> 
*/

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		search_n(char *buffer);
int		ft_full_copy(char *buffer, char *remaining);
char	*ft_copy_head(char *buffer, int x);

#endif
