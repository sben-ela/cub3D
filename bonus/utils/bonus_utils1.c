/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:14:05 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/20 15:07:52 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void    ft_destroy(t_data *data)
{
	kill(data->pid, SIGKILL);
    mlx_destroy_window(data->mlx, data->win);
    exit (0);
}

void weapondire(int keypress, t_data *data)
{
	if (keypress == UP && data->up_down - 100 > -900)
		data->up_down -= 100;
	if (keypress == DOWN && data->up_down + 100 < 900)
		data->up_down += 100;
	if (keypress == LEFT && data->left_right - 100 > -600)
		data->left_right -= 100;
	if (keypress == RIGHT && data->left_right + 100 < 300)
		data->left_right += 100;
}

int on_key_down(int keypress, t_data *data)
{
	int pid;

	data->keypress = keypress;
    if (keypress == ESC)
		ft_destroy(data);
	weapondire(keypress, data);
	if (keypress == FIRE)
		data->flag = 1;
	if (keypress == RELOAD)
		data->reload = 1, ft_voice("textures/reload.mp3", &pid);
	if (keypress == OPEN)
		open_door(data);
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

int handle_mouse(int x, int y, t_data *data)
{
	double	dx;
	int		pos_x;
	int		pos_y;

	if (x < 0 || x >= WIDTH)
	{
		pos_x = 0;
		if (x < 0)
			pos_x = WIDTH - 1;
		mlx_mouse_move(data->win, pos_x, y);
		data->last_x = pos_x;
		x = pos_x;
	}
	if (y >= HEIGHT || y < 0)
	{
		pos_y = 0;
		if (y < 0)
			pos_y = HEIGHT - 1;
		mlx_mouse_move(data->win, pos_x, pos_y);
		data->last_y = pos_y;
		y = pos_y;
	}
	if (y - data->last_y > 0)
		data->up_down -= 4;
	else
		data->up_down += 4;
	data->last_y = y;
	dx = x - data->last_x;
	data->angle = (-dx * M_PI) / WIDTH;
	data->last_x = x;
	return (0);
}
