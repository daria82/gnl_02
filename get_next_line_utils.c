/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:34:08 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/19 15:02:51 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < (int)ft_strlen(s))
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, (ft_strlen(s1) + 1));
	ft_strlcat(s3, (char *)s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return ((char *)s3);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
	{
	int		ssize;
	size_t	ret2;
	size_t	j;
	size_t	dstj;
	size_t	i;

	ssize = size - 1;
	i = 0;
	ret2 = size;
	if ((int)ft_strlen(dst) <= ssize)
	{
		ret2 = ft_strlen(dst);
		j = ssize - ft_strlen(dst);
		dstj = ft_strlen(dst);
		while (i < j && src[i] != '\0')
		{
			dst[dstj] = src[i];
			i++;
			dstj++;
		}
		dst[dstj] = '\0';
	}
	return (ft_strlen(src) + ret2);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	search_n(char *buffer)
{
	int	i;

	i = 0;
	if (buffer == 0) //??
		return(-1);
	while(*(buffer + i) != '\n' && *(buffer + i) != '\0')
		i++;
	if (*(buffer + i) == '\0')
		i = -1;
	return(i);
}

int	ft_full_copy(char *buffer, char *remaining)
{
	int i;

	i = 0;
	while (*(remaining + i) != '\0')
	{
		*(buffer + i) = *(remaining + i);
		i++;
	}
	*(buffer + i) = *(remaining + i);
	return(0);	
}

char	*ft_copy_head(char *buffer, int x)
{
	char *ret;

	ret = (char *)malloc(x * sizeof(char));
	*(ret + x) = '\0';
	while (x > 0)
	{
		x--;
		*(ret + x) = *(buffer + x);
	}
	return(ret);
}
