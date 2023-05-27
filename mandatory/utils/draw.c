/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:56:12 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/27 18:28:49 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_floor_and_ceiling(t_data *data)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		color = data->ceiling;
		while (j < HEIGHT)
		{
			if (j > HEIGHT / 2)
				color = data->floor;
			ft_put_pixel(&data->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_data *data, double ray_x, double ray_y, double len)
{
	int		i;
	double	x_pixel;
	double	y_pixel;

	i = 0;
	x_pixel = data->player.x * CELL_SIZE;
	y_pixel = data->player.y * CELL_SIZE;
	while (i < CELL_SIZE * len)
	{
		ft_put_pixel(&data->img, x_pixel, y_pixel, RED);
		x_pixel += ray_x;
		y_pixel += ray_y;
		i++;
	}
}

void	draw_rays(t_data *data)
{
	int		i;
	double	cam_x;
	double	ray_x;
	double	ray_y;
	t_dist	dist;

	i = 0;
	while (i < WIDTH)
	{
		cam_x = ((2.0 * i - WIDTH) / WIDTH);
		ray_x = data->player.dir_x + cam_x * data->player.plane_x;
		ray_y = data->player.dir_y + cam_x * data->player.plane_y;
		dist = dda(data, ray_x, ray_y);
		draw_walls(data, HEIGHT / dist.distance, i, dist.wall_x);
		i++;
	}
}

void	draw_walls(t_data *data, double len, int x, double wallx)
{
	t_img	*texture;
	int		skipped;
	int		i;

	texture = &data->texture[data->compass - 1];
	skipped = 0;
	data->start = HEIGHT / 2 - len / 2;
	data->end = HEIGHT / 2 + len / 2;
	if (data->start < 0)
	{
		skipped = -data->start;
		data->start = 0;
	}
	if (data->end > HEIGHT)
		data->end = HEIGHT;
	i = 0;
	data->x_prime = texture->width * wallx;
	while (data->start + i < data->end)
	{
		data->y_prime = ((i + skipped) / len) * texture->height;
		ft_put_pixel(&data->img, x, data->start + i,
			ft_get_pixel(texture, data->x_prime, data->y_prime));
		i++;
	}
}
