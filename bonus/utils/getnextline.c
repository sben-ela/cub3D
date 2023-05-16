/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:08:13 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/05 15:13:57 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

#	ifndef BUFFER_SIZE
# 		define BUFFER_SIZE 10
#	endif

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i++;
	}
    return (0);
}

char	*ft_join(char *left_str, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!left_str)
	{
		left_str = malloc(1);
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(ft_strlen(left_str) + ft_strlen(buff) + 1);
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (left_str[++i] != '\0')
		str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ft_line(char *string)
{
	int		i;
	char	*dst;

	i = 0;
	if (!string[i])
		return (0);
	while (string[i] && string[i] != '\n')
		i++;
	if (string[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (0);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		dst[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

char	*ft_new_static_string(char *string)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (0);
	}
	dst = malloc(ft_strlen(string) - i + 1);
	if (!dst)
		return (0);
	i++;
	j = 0;
	while (string[i])
		dst[j++] = string[i++];
	dst[j] = '\0';
	free(string);
	return (dst);
}

char	*ft_check_new_line(int fd, char *string)
{
	char	*buff;
	int		i;

	i = 1;
	buff = malloc(BUFFER_SIZE + (size_t)1);
	if (!buff)
		return (0);
	while (!ft_strchr(string, '\n') && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			if (string)
				free(string);
			return (0);
		}
		buff[i] = '\0';
		string = ft_join(string, buff);
	}
	free(buff);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	string = ft_check_new_line(fd, string);
	if (!string)
		return (0);
	line = ft_line(string);
	string = ft_new_static_string(string);
	return (line);
}