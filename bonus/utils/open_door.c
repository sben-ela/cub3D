/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:12:20 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/18 10:46:06 by sben-ela         ###   ########.fr       */
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
