/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:05:49 by sben-ela          #+#    #+#             */
/*   Updated: 2023/04/30 11:34:35 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_put_pixel(t_img *img, int x, int y, int rgb)
{
	int	offset;
	int	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	offset = x * img->bpp / 8 + img->size_line * y;
	dst = (int *)(img->addr + offset);
	*dst = rgb; 
}

void	rotate(double *x_prime, double *y_prime, double angle)
{
	double	x;
	double	y;

	x = *x_prime * cos(angle) - *y_prime * sin(-angle);
	y = *x_prime * sin(-angle) + *y_prime * cos(angle);
	*x_prime = x;
	*y_prime = y;
}

void    ft_putcube(t_data *data, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < CELL_SIZE - 1)
    {
        j = 0;
        while (j < CELL_SIZE - 1)
        {
            ft_put_pixel(&data->img, x * CELL_SIZE + j, y * CELL_SIZE + i, color);
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
	int 	i;
	double	cam;
	double	ray[2];
	t_dist	dist;

	i = 0;
	while (i < WIDTH)
	{
		cam = ((2.0 * i - WIDTH) / WIDTH);
		ray[0] = data->player.dir_x + cam * data->player.plane_x;
		ray[1] = data->player.dir_y + cam * data->player.plane_y;
		dist = dda(data, ray[0], ray[1], 0);
		// draw_line(data, ray[0], ray[1], dist.distance);
		draw_walls(data, HEIGHT / dist.distance, i, dist.wall_x);
		i++;
	}
}

void	ft_putplayer(t_data *data, double x, double y, int color)
{
	int i;
	int j;

	i = -PLAYER_SIZE / 2;
	while (i < PLAYER_SIZE / 2)
	{
		j = -PLAYER_SIZE / 2;
		while (j < PLAYER_SIZE / 2)
		{
			ft_put_pixel(&data->img, x * CELL_SIZE + i, y * CELL_SIZE + j, color);
			j++;
		}
		i++;
	}
	// draw_line(data, data->player.dir_x, data->player.dir_y, 2);
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

void	moves(t_data *data)
{
	double	direction;
	double	x;
	double	y;

	if (data->hooks.rotation != -1)
	{
		direction = (1.0 - 2.0 * (data->hooks.rotation == KEY_RIGHT));
		rotate(&data->player.dir_x, &data->player.dir_y, direction * ROT_ANGLE);
		rotate(&data->player.plane_x, &data->player.plane_y, direction * ROT_ANGLE);
	}
	if (data->hooks.vertical != -1)
	{
		direction = (1.0 - 2.0 * (data->hooks.vertical == KEY_S));
		x = data->player.dir_x * TRANS_SPEED * direction;
		y = data->player.dir_y * TRANS_SPEED * direction;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + 3 * x)] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + 3 * x)] != 'D')
			data->player.x += x;
		if (data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != '1'&& data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != 'D')
			data->player.y += y;
	}
	if (data->hooks.horizontal != -1)
	{
		direction = (1.0 - 2.0 * (data->hooks.horizontal == KEY_A));
		x = -data->player.dir_y * TRANS_SPEED * direction;
		y = data->player.dir_x * TRANS_SPEED * direction;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + x * 3)] != '1' && data->map[(int)(data->player.y)][(int)(data->player.x + x * 3)] != 'D')
			data->player.x += x;
		if (data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != '1' && data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != 'D')
			data->player.y += y;
	}
}

int frame(t_data *data)
{
	data->sdoor.distance = -1;
	data->sdoor.flag = 0;
    new_image(data);
	moves(data);
	draw_floor_and_celing(data);
	draw_rays(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.img);
    return (0);
}