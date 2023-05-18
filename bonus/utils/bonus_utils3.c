/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:10:54 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/18 10:10:55 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	draw_line(data, data->player.dir_x, data->player.dir_y, 2);
}

int	ft_get_pixel(t_img *img, int x, int y)
{
	int	offset;
	int	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return 0;
	offset = x * img->bpp / 8 + img->size_line * y;
	dst = (int *)(img->addr + offset);
	return (*dst);
}

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

void	new_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
	&data->img.size_line, &data->img.endian);
}