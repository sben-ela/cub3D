/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:13:08 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/27 23:13:10 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	set_elements(char **s)
{
	s[0] = "NO ";
	s[1] = "SO ";
	s[2] = "WE ";
	s[3] = "EA ";
	s[4] = "F ";
	s[5] = "C ";
	s[6] = NULL;
}

void	check_count(char **map, char **elements)
{
	int	i;
	int	j;
	int	count;

	j = 0;
	while (elements[j])
	{
		i = 0;
		count = 0;
		while (map[i] && !is_map_line(map[i]))
		{
			if (!ft_strncmp(map[i], elements[j], ft_strlen(elements[j])))
				count++;
			i++;
		}
		if (count != 1)
		{
			printf("check elements on map file :(\n");
			exit(1);
		}
		j++;
	}
}

void	check_path(char **map, char **elements)
{
	int	i;
	int	index;

	i = 0;
	while (elements[i])
	{
		index = get_index_(elements[i], map);
		if (!map[index][2] || (map[index][2] && is_empty(&map[index][2])))
		{
			printf("paths must be set :(\n");
			exit(1);
		}
		i++;
	}
}

void	check_elements(char **map)
{
	char	*elements[7];
	int		i;

	i = 0;
	while (map[i])
	{
		if (!map[i][0] || is_empty(map[i]) || !ft_strncmp(map[i], "NO ", 3)
			|| !ft_strncmp(map[i], "SO ", 3) || !ft_strncmp(map[i], "WE ", 3)
			|| !ft_strncmp(map[i], "EA ", 3) || !ft_strncmp(map[i], "F ", 2)
			|| !ft_strncmp(map[i], "C ", 2) || is_map_line(map[i]))
			i++;
		else
		{
			printf("check elements on map file :(\n");
			exit(1);
		}
	}
	set_elements(elements);
	check_count(map, elements);
	check_path(map, elements);
}
