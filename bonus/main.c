/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:57:53 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/28 22:07:25 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_destroy(t_data *data)
{
	kill(data->pid, SIGKILL);
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
}

void	init_weapon(t_data *data)
{
	int			hight;
	int			width;
	char		*str;
	int			i;

	i = 0;
	while (i < 84)
	{
		str = ft_strjoin(ft_itoa(i + 1), ".xpm");
		data->weapon[i] = mlx_xpm_file_to_image(data->mlx,
				ft_strjoin("weapon/", str), &width, &hight);
		if (!data->weapon[i])
			(printf("invalid texture"), exit (1));
		if (i % 10 == 0)
			printf("\033[0;32m waiting ...\033[0m\n");
		i++;
	}
	data->weapon[i] = 0;
}

void	init_textures(t_data *data, int i, int hight, int width)
{
	data->door.img = mlx_xpm_file_to_image(data->mlx,
			"textures/door_1.xpm", &data->door.width, &data->door.height);
	data->fire = mlx_xpm_file_to_image(data->mlx, "weapon/fire.xpm",
			&width, &hight);
	if (!data->door.img || ! data->fire)
		(printf("invalid door"), exit (1));
	data->door.addr = mlx_get_data_addr(data->door.img, &data->door.bpp,
			&data->door.size_line, &data->door.endian);
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->paths[i],
				&data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].img)
		{
			printf("invalid texture\n");
			exit (EXIT_FAILURE);
		}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bpp, &data->texture[i].size_line,
				&data->texture[i].endian);
		if (!data->texture[i].addr)
			exit (EXIT_FAILURE);
		i++;
	}
	init_weapon(data);
}

void	init_data(t_data *data, char *map)
{
	data->ceiling = CEILING;
	data->floor = FLOOR;
	data->fd = open(map, O_RDONLY);
	if (data->fd < 0)
		(printf("bad file disncriptor :)\n"), exit (1));
	data->count = count_line(map);
	data->map = get_map(data->fd, data->count);
	check_file(data->map, data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	init_textures(data, 0, 0, 0);
	get_player_pos(&data->player, data->map);
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.65;
	data->player.plane_y = 0;
	data->left_right = 0;
	data->up_down = 0;
	data->hooks.horizontal = -1;
	data->hooks.vertical = -1;
	data->hooks.rotation = -1;
	data->last_x = WIDTH / 2;
	data->last_y = HEIGHT / 2;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (0);
	data = malloc(sizeof(t_data));
	init_data(data, av[1]);
	fix_direction(data);
	mlx_hook(data->win, ON_KEYDOWN, 0, on_key_down, data);
	mlx_hook(data->win, ON_KEYUP, 0, on_key_up, data);
	mlx_hook(data->win, ON_MOUSEMOVE, 0, handle_mouse, data);
	mlx_loop_hook(data->mlx, frame, data);
	ft_voice("textures/player.mp3", &data->pid);
	mlx_loop(data->mlx);
	return (0);
}
