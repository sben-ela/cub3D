/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:54:56 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/27 15:03:46 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_wall(t_data *data, t_dist *dist, double ray_x, double ray_y)
{
	if (data->map[data->pos_y][data->pos_x] == '1')
	{
		if (data->side == VER)
		{
			dist->distance = data->delta_x - data->s_delta_x;
			dist->wall_x = data->player.y + (dist->distance * ray_y);
			dist->wall_x -= (int)dist->wall_x;
			data->compass = EAST;
			if (ray_x < 0)
				data->compass = WEST;
			return (1);
		}
		dist->distance = data->delta_y - data->s_delta_y;
		dist->wall_x = data->player.x + (dist->distance * ray_x);
		dist->wall_x -= (int)dist->wall_x;
		data->compass = NORTH;
		if (ray_y > 0)
			data->compass = SOUTH;
		return (1);
	}
	return (0);
}

void	_dda(t_data *data, t_dist *dist, double ray_x, double ray_y)
{
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
		if (check_wall(data, dist, ray_x, ray_y))
			return ;
	}
}

t_dist	dda(t_data *data, double ray_x, double ray_y)
{
	t_dist	dist;

	data->step_x = -1;
	data->step_y = -1;
	data->pos_x = (int)data->player.x;
	data->pos_y = (int)data->player.y;
	dist.distance = 0;
	data->s_delta_x = 1.0 / fabs(ray_x);
	data->s_delta_y = 1.0 / fabs(ray_y);
	data->delta_x = ((int)data->player.x + 1 - data->player.x)
		* data->s_delta_x;
	data->delta_y = ((int)data->player.y + 1 - data->player.y)
		* data->s_delta_y;
	if (ray_x < 0)
		data->delta_x = (data->player.x - (int)data->player.x)
			* data->s_delta_x;
	if (ray_y < 0)
		data->delta_y = (data->player.y - (int)data->player.y)
			* data->s_delta_y;
	if (ray_x > 0)
		data->step_x = 1;
	if (ray_y > 0)
		data->step_y = 1;
	_dda(data, &dist, ray_x, ray_y);
	return (dist);
}
