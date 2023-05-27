/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:56:00 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/26 21:36:19 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_textures(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->paths[i], &data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].img)
		{
			ft_error("invalid texure");
		}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img, &data->texture[i].bpp, &data->texture[i].size_line, &data->texture[i].endian);
		if (!data->texture[i].addr)
			ft_error("mlx_get_data_addr failed\n");
		i++;
	}
}

void	init_data(t_data *data, char *map)
{
	data->ceiling = NONE;
	data->floor = GREY;
	data->fd = open(map, O_RDONLY);
	if (data->fd < 0)
		ft_error("bad file :(");
	data->count = count_line(map);
	data->map = get_map(data->fd, data->count);
	check_file(data->map, data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	init_textures(data);
	get_player_pos(&data->player, data->map);
	data->player.dir_x = 0;
	data->player.dir_y = -1; 
	data->player.plane_x = 0.65;
	data->player.plane_y = 0;
	data->hooks.horizontal = -1;
	data->hooks.vertical = -1;
	data->hooks.rotation = -1;
}

void	get_direction(t_data *data)
{
	char	*dierection = "NSEW";
	int 	i;

	i = 0;
	while (dierection[i])
	{
		if (data->map[(int)data->player.y][(int)data->player.x] == dierection[i])
		{
			data->player.direction = i + 1;
			return ;
		}
		i++;
	}
}

void	fix_direction(t_data *data)
{
	double angle;
	get_direction(data);

	angle = 0;
	if (data->player.direction == EAST)
		angle = -M_PI / 2;
	else if (data->player.direction == WEST)
		angle = M_PI / 2;
	else if (data->player.direction == SOUTH)
		angle = M_PI;
	rotate(&data->player.dir_x, &data->player.dir_y, angle);
	rotate(&data->player.plane_x, &data->player.plane_y, angle);
}

int	main(int ac, char **av)
{
	t_data 		*data;

	check_args(ac, av);
	data = malloc(sizeof(t_data));
	init_data(data, av[1]);
	fix_direction(data);
	mlx_hook(data->win, ON_KEYDOWN, 0, on_key_down, data);
	mlx_hook(data->win, ON_KEYUP, 0, on_key_up, data);
	if (mlx_loop_hook(data->mlx, frame, data) == -1)
		ft_error("mlx_loop_hook failed");
	mlx_loop(data->mlx);
	return (0);
}
