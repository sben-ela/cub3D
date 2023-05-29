/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:17:12 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/27 23:46:53 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../cub.h"

int	getmapsize(char **map, int index)
{
	int	size;

	size = 1;
	while (map[index] && !is_empty(map[index]))
	{
		index++;
		size++;
	}
	return (size);
}

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	get_index(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_map_line(map[i]))
			return (i);
		i++;
	}
	printf("check map file :(\n");
	exit(1);
}

int	get_largest(char **map, int index)
{
	int	ret;

	ret = index;
	while (map[index])
	{
		if (ft_strlen(map[index]) > ft_strlen(map[ret]))
			ret = index;
		index++;
	}
	return (ft_strlen(map[ret]));
}
