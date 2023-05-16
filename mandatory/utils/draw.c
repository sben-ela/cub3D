/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:56:12 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/16 08:09:35 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_floor_and_celing(t_data *data)
{
    int i;
    int j;
    int color;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        color = data->celing;
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
	double	cam;
	double	ray[2];
	t_dist	dist;

	i = 0;
	while (i < WIDTH)
	{
		cam = ((2.0 * i - WIDTH) / WIDTH);
		ray[0] = data->player.dir_x + cam * data->player.plane_x;
		ray[1] = data->player.dir_y + cam * data->player.plane_y;
		dist = dda(data, ray[0], ray[1]);
		draw_walls(data, HEIGHT / dist.distance, i, dist.wall_x);
		i++;
	}
}
// cam = -1 ==> ray[0] = -0.65 & ray[1] = -1
// cam =  1 ==> ray[0] =  0.65 & ray[1] = -1
// com =  0 ==> ray[0] =  0	   & ray[1] = -1
 
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
	skipped = 0;
	start = HEIGHT / 2 - len / 2;
	end = HEIGHT / 2 + len / 2;
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
