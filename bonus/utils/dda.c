/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:54:56 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/18 10:53:28 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_dist dda(t_data *data, double ray_x, double ray_y)
{
	t_dist	dist;
	double	distance;

	data->step_x = -1;
	data->step_y = -1;
	data->pos_x = (int)data->player.x;
	data->pos_y = (int)data->player.y;
	distance = 0;
	data->s_delta_x = 1.0 / fabs(ray_x);
	data->s_delta_y = 1.0 / fabs(ray_y);
	data->delta_x = ((int)data->player.x + 1 - data->player.x) * data->s_delta_x;
	data->delta_y = ((int)data->player.y + 1 - data->player.y) * data->s_delta_y;
	if (ray_x < 0)
		data->delta_x = (data->player.x - (int)data->player.x) * data->s_delta_x;
	if (ray_y < 0)
		data->delta_y = (data->player.y - (int)data->player.y) * data->s_delta_y;
	if (ray_x > 0)
		data->step_x = 1;
	if (ray_y > 0)
		data->step_y = 1;
	while (1)
	{
		if (data->delta_x < data->delta_y)
		{
			data->delta_x += data->s_delta_x;
			data->pos_x += data->step_x;
			data->side = VER;
		}
		else
		{
			data->delta_y += data->s_delta_y;
			data->pos_y += data->step_y;
			data->side = HOR;
		}
		if (data->map[data->pos_y][data->pos_x] == '1' || data->map[data->pos_y][data->pos_x] == 'D')
		{
			data->hitted = DOOR - (data->map[data->pos_y][data->pos_x] == '1');
			if (data->side == VER)
			{
				distance = data->delta_x - data->s_delta_x;
				dist.wall_x = data->player.y + (distance * ray_y);
				dist.wall_x -= (int)dist.wall_x;
				data->compass = EAST;
				if (ray_x < 0)
					data->compass = WEST;
				break ;
			}
			distance = data->delta_y - data->s_delta_y;
			dist.wall_x = data->player.x + (distance * ray_x);
			dist.wall_x -= (int)dist.wall_x;
			data->compass = NORTH;
			if (ray_y > 0)
				data->compass = SOUTH;
			break ;
		}
	}
	dist.distance = distance;
	return(dist);
}