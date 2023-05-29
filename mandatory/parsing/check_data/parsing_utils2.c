/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:36:59 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/27 23:37:44 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	fill_characters(int *characters)
{
	characters[0] = 0;
	characters[1] = 0;
	characters[2] = 0;
	characters[3] = 0;
	characters[4] = 0;
}

void	fill_space(char **copy, int largest, char **map, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < getmapsize(map, index) - 1)
	{
		copy[i] = malloc((largest + 1) * sizeof(char));
		j = 0;
		while (j < largest)
		{
			copy[i][j] = ' ';
			j++;
		}
		copy[i][j] = 0;
		i++;
	}
	copy[i] = 0;
}

void	copy_init(char **copy, char **map, int index, int largest)
{
	int	i;
	int	size;

	i = 0;
	size = getmapsize(map, index) - 1;
	fill_space(copy, largest, map, index);
	while (i < size)
	{
		ft_strcpy(copy[i], map[index]);
		i++;
		index++;
	}
}
