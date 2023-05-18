/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:12:20 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/18 10:12:23 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	open_door(t_data *data)
{
	int	x;
	int	y;
	int	pid;

	x = data->player.x + data->player.dir_x;
	y = data->player.y + data->player.dir_y;
	if (data->map[y][x] != 'D' && data->map[y][x] != 'O')
		return ;
	data->map[y][x] = 79 - 11 * (data->map[y][x] == 'O');
	ft_voice("textures/open_door.mp3", &pid);
}

int	count_line_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		i++;
	}
	return (i);
}
