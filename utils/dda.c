/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:54:56 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/05 15:14:11 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


t_dist dda(t_data *data, double ray_x, double ray_y)
{
	t_dist	dist;
	int		pos_x;
	int		pos_y;
	double	s_delta_x;
	double	s_delta_y;
	double	delta_x;
	double	delta_y;
	double	distance;
	int		step_x;
	int		step_y;

	step_x = -1;
	step_y = -1;
	pos_x = (int)data->player.x;
	pos_y = (int)data->player.y;
	distance = 0;
	s_delta_x = 1.0 / fabs(ray_x);
	s_delta_y = 1.0 / fabs(ray_y);
	delta_x = ((int)data->player.x + 1 - data->player.x) * s_delta_x;
	delta_y = ((int)data->player.y + 1 - data->player.y) * s_delta_y;
	if (ray_x < 0)
		delta_x = (data->player.x - (int)data->player.x) * s_delta_x;
	if (ray_y < 0)
		delta_y = (data->player.y - (int)data->player.y) * s_delta_y;
	if (ray_x > 0)
		step_x = 1;
	if (ray_y > 0)
		step_y = 1;
	while (1)
	{
		if (delta_x < delta_y)
		{
			delta_x += s_delta_x;
			pos_x += step_x;
			data->side = VER;
		}
		else
		{
			delta_y += s_delta_y;
			pos_y += step_y;
			data->side = HOR;
		}
		if (data->map[pos_y][pos_x] == '1' || data->map[pos_y][pos_x] == 'D')
		{
			data->hitted = DOOR - (data->map[pos_y][pos_x] == '1');
			distance = delta_y - s_delta_y;
			dist.wall_x = data->player.x + (distance * ray_x);
			dist.wall_x -= (int)dist.wall_x;
			data->compass = NORTH;
				if (ray_y > 0)
					data->compass = SOUTH;
			if (data->side == VER)
			{
				distance = delta_x - s_delta_x;
				dist.wall_x = data->player.y + (distance * ray_y);
				dist.wall_x -= (int)dist.wall_x;
				data->compass = EAST;
				if (ray_x < 0)
					data->compass = WEST;
			}
			if (data->map[pos_y][pos_x] == 'D')
			{
				data->sdoor.x = pos_x;
				data->sdoor.y = pos_y;
				data->sdoor.distance = distance;
			}
			break ;
		}
	}
	dist.distance = distance;
	return(dist);
}
