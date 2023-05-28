/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:11:22 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/28 16:29:26 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_direction(t_data *data)
{
	char	*dierection;
	int		i;

	i = 0;
	dierection = "NSEW";
	while (dierection[i])
	{
		if (data->map[(int)data->player.y]
			[(int)data->player.x] == dierection[i])
		{
			data->player.direction = i + 1;
			return ;
		}
		i++;
	}
}

void	fix_direction(t_data *data)
{
	double	angle;

	angle = 0;
	get_direction(data);
	if (data->player.direction == EAST)
		angle = -M_PI / 2;
	else if (data->player.direction == WEST)
		angle = M_PI / 2;
	else if (data->player.direction == SOUTH)
		angle = M_PI;
	rotate(&data->player.dir_x, &data->player.dir_y, angle);
	rotate(&data->player.plane_x, &data->player.plane_y, angle);
}

void	start_init(t_data *data)
{
	data->start_x = data->player.x - 15;
	if (data->start_x < 0)
		data->start_x = 0;
	data->end_x = data->player.x + 15;
	if (data->end_x > ft_strlen(data->map[data->start_y]))
		data->end_x = ft_strlen(data->map[data->start_y]);
}

char	**ft_get_new_map(t_data *data, int i, int j, char **map)
{
	map = malloc(sizeof(char *) * 31);
	while (data->start_y < data->end_y)
	{
		map[i] = malloc(31);
		start_init(data);
		j = 0;
		while (data->start_x < data->end_x)
		{
			if (data->start_y == (int)data->player.y
				&& data->start_x == (int)data->player.x)
				map[i][j] = 'P';
			else
				map[i][j] = data->map[data->start_y][data->start_x];
			data->start_x++;
			j++;
		}
		map[i][j] = 0;
		i++;
		data->start_y++;
	}
	return (map[i] = 0, map);
}

void	weapon(t_data *data)
{
	int	pid;

	ft_voice("weapon/fire.mp3", &pid);
	mlx_put_image_to_window(data->mlx, data->win,
		data->fire, 585 + data->left_right, 660);
	mlx_put_image_to_window(data->mlx, data->win,
		data->fire, 585 + data->left_right, 650);
}
