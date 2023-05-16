/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:56:00 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/16 10:59:32 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_textures(t_data *data)
{
	data->texture[0].img = mlx_xpm_file_to_image(data->mlx, "../bonus/textures/wall5.xpm", &data->texture[0].width, &data->texture[0].height);
	data->texture[0].addr = mlx_get_data_addr(data->texture[0].img, &data->texture[0].bpp, &data->texture[0].size_line, &data->texture[0].endian);
	data->texture[1].img = mlx_xpm_file_to_image(data->mlx, "../bonus/textures/wall2.xpm", &data->texture[1].width, &data->texture[1].height);
	data->texture[1].addr = mlx_get_data_addr(data->texture[1].img, &data->texture[1].bpp, &data->texture[1].size_line, &data->texture[1].endian);
	data->texture[2].img = mlx_xpm_file_to_image(data->mlx, "../bonus/textures/wall.xpm", &data->texture[2].width, &data->texture[2].height);
	data->texture[2].addr = mlx_get_data_addr(data->texture[2].img, &data->texture[2].bpp, &data->texture[2].size_line, &data->texture[2].endian);
	data->texture[3].img = mlx_xpm_file_to_image(data->mlx, "../bonus/textures/wall3.xpm", &data->texture[3].width, &data->texture[3].height);
	data->texture[3].addr = mlx_get_data_addr(data->texture[3].img, &data->texture[3].bpp, &data->texture[3].size_line, &data->texture[3].endian);
}

int	ft_get_pixel(t_img *img, int x, int y)
{
	int	offset;
	int	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return 0;
	// the bpp = 32 bit so the number of bytes represent each pixel is bpp / 8
	offset = (x * img->bpp / 8) + img->size_line * y;
	dst = (int *)(img->addr + offset);
	return (*dst);
}

void	init_data(t_data *data, char *map)
{
	data->celing = CELING;
	data->floor = FLOOR;
	data->fd = open(map, O_RDONLY);
	if (data->fd < 0)
		printf("bad file :(\n"), exit (1);
	data->count = count_line(map);
	data->map = get_map(data->fd, data->count);
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

int	main(int ac, char **av)
{
	t_data 		*data;

	if (ac != 2)
	    return (0);
	data = malloc(sizeof(t_data));
	init_data(data, av[1]);
	mlx_hook(data->win, ON_KEYDOWN, 0, on_key_down, data);
	mlx_hook(data->win, ON_KEYUP, 0, on_key_up, data);
	mlx_loop_hook(data->mlx, frame, data);
	mlx_loop(data->mlx);
	return (0);
}
