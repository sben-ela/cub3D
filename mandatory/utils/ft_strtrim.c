/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:50:36 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/23 22:37:40 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*ft_fill(char	*ptr, char	*str, int start, int last)
{
	int	i;

	i = 0;
	while (start <= last)
	{
		ptr[i] = str[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int	ft_isintrim(char letter, char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (letter != str[i])
			i++;
		else
			return (1);
	}
	return (0);
}

static int	ft_first(char	*str, char	*set)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && ft_isintrim(str[i], set))
	{
		i++;
	}
	return (i);
}

static int	ft_last(char	*str, char	*set, int i)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len >= i && ft_isintrim(str[len], set))
	{
			len--;
	}
	return (len);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	char	*str;
	char	*trim;
	char	*ptr;
	int    	i;

	if (!s1 || !set)
		return (NULL);
	str = (char *)s1;
	trim = (char *)set;
	i = ft_first(str, trim);
	if (i == ft_strlen(str))
	{
		ptr = malloc(1 * sizeof(char));
		ptr[0] = 0;
		return (ptr);
	}
	ptr = (char *)malloc((ft_last(str, trim, i) - i) + 2);
	if (!ptr)
		return (NULL);
	ft_fill(ptr, str, i, ft_last(str, trim, i));
	return (ptr);
}
