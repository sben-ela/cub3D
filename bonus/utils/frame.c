/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:05:49 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/18 21:11:34 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rotate(double *x_prime, double *y_prime, double angle)
{
	double	x;
	double	y;

	x = *x_prime * cos(angle) - *y_prime * sin(-angle);
	y = *x_prime * sin(-angle) + *y_prime * cos(angle);
	*x_prime = x;
	*y_prime = y;
}

void	_moves(t_data *data, int direction)
{
	double	x;
	double	y;

	if (data->hooks.vertical != -1)
	{
		direction = (1.0 - 2.0 * (data->hooks.vertical == KEY_S));
		x = data->player.dir_x * TRANS_SPEED * direction;
		y = data->player.dir_y * TRANS_SPEED * direction;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + 3 * x)] != '1'
			&& data->map[(int)(data->player.y)][(int)(data->player.x + 3 * x)] != 'D')
			data->player.x += x;
		if (data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != '1'
		&& data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != 'D')
			data->player.y += y;
	}
	if (data->hooks.horizontal != -1)
	{
		direction = (1.0 - 2.0 * (data->hooks.horizontal == KEY_A));
		x = -data->player.dir_y * TRANS_SPEED * direction;
		y = data->player.dir_x * TRANS_SPEED * direction;
		if (data->map[(int)(data->player.y)][(int)(data->player.x + 3 * x)] != '1'
		&& data->map[(int)(data->player.y)][(int)(data->player.x + 3 * x)] != 'D')
			data->player.x += x;
		if (data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != '1'
		&& data->map[(int)(data->player.y + 3 * y)][(int)(data->player.x)] != 'D')
			data->player.y += y;
	}
}

void	moves(t_data *data)
{
	int	direction;


	rotate(&data->player.dir_x, &data->player.dir_y, data->angle);
	rotate(&data->player.plane_x, &data->player.plane_y, data->angle);
	data->angle = 0;
	if (data->hooks.rotation != -1)
	{
		direction = (1.0 - 2.0 * (data->hooks.rotation == KEY_RIGHT));
		rotate(&data->player.dir_x, &data->player.dir_y, direction * ROT_ANGLE);
		rotate(&data->player.plane_x, &data->player.plane_y, direction * ROT_ANGLE);
	}
	_moves(data, 0);
}

void	Weapon(t_data *data)
{
	int	pid;

	ft_voice("weapon/fire.mp3", &pid);
	mlx_put_image_to_window(data->mlx, data->win, data->fire, 585 + data->left_right, 660);
	mlx_put_image_to_window(data->mlx, data->win, data->fire, 585 + data->left_right, 650);
}

int frame(t_data *data)
{
	static int i;

    new_image(data);
	moves(data);
	draw_floor_and_ceiling(data);
    draw_minimap(data);
	draw_rays(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	if (data->reload == 1)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->weapon[i % 84], -80 + data->left_right, 280);
		if (i % 84 == 0)
			data->reload = -1;
		i++;
	}
	else
		mlx_put_image_to_window(data->mlx, data->win, data->weapon[0], -80 + data->left_right, 280);
	if (data->flag == 1 && data->reload != 1)
		Weapon(data);
	data->flag = 0;
    mlx_destroy_image(data->mlx, data->img.img);
    return (0);
}
