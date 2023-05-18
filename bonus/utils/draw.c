/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:10:40 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/18 21:44:38 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	int 	i;
	double	cam;
	double	ray_x;
	double	ray_y;
	t_dist	dist;

	i = 0;

	while (i < WIDTH)
	{
		cam = ((2.0 * i - WIDTH) / WIDTH);
		ray_x = data->player.dir_x + cam * data->player.plane_x;
		ray_y = data->player.dir_y + cam * data->player.plane_y;
		dist = dda(data, ray_x, ray_y);
		draw_walls(data, HEIGHT / dist.distance, i, dist.wall_x);
		draw_line(data, ray_x, ray_y, dist.distance);
		i++;
	}
}

void	draw_walls(t_data *data, double len, int x, double wallx)
{
	double	start;
	double	end;
    double	x_prime;
	double	y_prime;
	t_img	*texture;
	int		skipped;
	int		i;

	texture = &data->texture[data->compass - 1];
	if (data->hitted == DOOR)
		texture = &data->door;
	skipped = 0;
	start = HEIGHT / 2 - len / 2 - data->up_down;
	end = HEIGHT / 2 + len / 2 - data->up_down;
	if (start < 0)
	{
		skipped = -start;
		start = 0;
	}
	if (end > HEIGHT)
		end = HEIGHT;
    i = 0;
    x_prime = texture->width * wallx;
	while (start + i < end)
	{
		y_prime = ((i + skipped) / len) * texture->height;
		ft_put_pixel(&data->img, x, start + i, ft_get_pixel(texture, x_prime, y_prime));
        i++;
	}
}

void draw_floor_and_ceiling(t_data *data)
{
    int i;
    int j;
    int color;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        color = BLACK;
        while (j < HEIGHT)
        {
            if (j > HEIGHT / 2 - data->up_down)
                color = NONE;
            ft_put_pixel(&data->img, i, j, color);
            j++;
        }
        i++;
    }    
}

void    draw_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while(data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				ft_putcube(data, x, y, BLACK);
			else if (data->map[y][x] == 'D')
				ft_putcube(data, x, y, RED);
			else if (data->map[y][x] == 'O')
				ft_putcube(data, x, y, GREEN);
			else
				ft_putcube(data, x, y, YELLOW);
			x++;
		}
		y++;
	}
	ft_putplayer(data, data->player.x, data->player.y, RED);
}
