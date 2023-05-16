/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:56:20 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/15 19:56:21 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

int on_key_down(int keypress, t_data *data)
{
	if (keypress == ESC)
		ft_destroy(data);
	if (keypress == KEY_W || keypress == KEY_S)
		data->hooks.vertical = keypress;
	if (keypress == KEY_A || keypress == KEY_D)
		data->hooks.horizontal = keypress;
	if (keypress == KEY_LEFT || keypress == KEY_RIGHT)
		data->hooks.rotation = keypress;
	return (0);
}

int on_key_up(int keypress, t_data *data)
{
    if (keypress == KEY_W || keypress == KEY_S)
        data->hooks.vertical = -1;
    if (keypress == KEY_A || keypress == KEY_D)
        data->hooks.horizontal = -1;
	if (keypress == KEY_LEFT || keypress == KEY_RIGHT)
		data->hooks.rotation = -1;
    return(0);
}