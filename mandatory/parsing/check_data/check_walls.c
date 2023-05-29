/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:26:59 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/27 23:35:17 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_otherside(char *line)
{
	int	i;

	i = ft_strlen(line);
	while (line[i - 1] == ' ')
		i--;
	if (line[i - 1] != '1')
	{
		printf("The map must be surrounded by walls\n"),
		exit(1);
	}
}

void	check_sides(char **map, int index)
{
	int	i;

	while (map[index] && !is_empty(map[index]))
	{
		i = 0;
		while (map[index][i])
		{
			while (map[index][i] == ' ')
				i++;
			if (map[index][i] != '1')
			{
				printf("The map must be surrounded by walls\n"),
				exit(1);
			}
			check_otherside(map[index]);
			break ;
		}
		index++;
	}
}

void	check_last(char **map, int index)
{
	int	i;

	i = 0;
	while (map[index] && !is_empty(map[index]))
		index++;
	index--;
	while (map[index][i])
	{
		if (map[index][i] != '1' && map[index][i] != ' ')
		{
			printf("The map must be surrounded by walls\n"),
			exit(1);
		}
		i++;
	}
}

void	check_first(char **map, int index)
{
	int	i;

	i = 0;
	while (map[index][i])
	{
		if (map[index][i] != '1' && map[index][i] != ' ')
		{
			printf("The map must be surrounded by walls\n"),
			exit(1);
		}
		i++;
	}
}

void	check_walls(int index, char **map, t_data *data)
{
	check_first(map, index);
	check_last(map, index);
	check_sides(map, index);
	check_corners(map, index, data);
}
