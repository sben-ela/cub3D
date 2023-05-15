#include "cub.h"

void	init_textures(t_data *data)
{
	data->door.img = mlx_xpm_file_to_image(data->mlx, "../textures/door_1.xpm", &data->door.width, &data->door.height);
	data->door.addr = mlx_get_data_addr(data->door.img, &data->door.bpp, &data->door.size_line, &data->door.endian);
	data->texture[0].img = mlx_xpm_file_to_image(data->mlx, "../textures/wall5.xpm", &data->texture[0].width, &data->texture[0].height);
	data->texture[0].addr = mlx_get_data_addr(data->texture[0].img, &data->texture[0].bpp, &data->texture[0].size_line, &data->texture[0].endian);
	data->texture[1].img = mlx_xpm_file_to_image(data->mlx, "../textures/wall2.xpm", &data->texture[1].width, &data->texture[1].height);
	data->texture[1].addr = mlx_get_data_addr(data->texture[1].img, &data->texture[1].bpp, &data->texture[1].size_line, &data->texture[1].endian);
	data->texture[2].img = mlx_xpm_file_to_image(data->mlx, "../textures/sben-ela.xpm", &data->texture[2].width, &data->texture[2].height);
	data->texture[2].addr = mlx_get_data_addr(data->texture[2].img, &data->texture[2].bpp, &data->texture[2].size_line, &data->texture[2].endian);
	data->texture[3].img = mlx_xpm_file_to_image(data->mlx, "../textures/wall3.xpm", &data->texture[3].width, &data->texture[3].height);
	data->texture[3].addr = mlx_get_data_addr(data->texture[3].img, &data->texture[3].bpp, &data->texture[3].size_line, &data->texture[3].endian);
}

void    init_data(t_data *data, char *map)
{
	data->celing = CELING;
	data->floor = FLOOR;
	data->fd = open(map, O_RDONLY);
	if (data->fd < 0)
		printf("bad file disncriptor :)\n"), exit (1);
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
	data->left_right = 0;
	data->up_down = 0;
	data->hooks.horizontal = -1;
	data->hooks.vertical = -1;
	data->hooks.rotation = -1;
	data->sdoor.x = -1;
	data->sdoor.y = -1;
	data->mouse_y = HEIGHT / 2;
	data->mouse_x = WIDTH / 2;
}

int	main(int ac, char **av)
{
	t_data 		*data;

	if (ac != 2 || !av[0])
	    return (0);
	data = malloc(sizeof(t_data));
	init_data(data, av[1]);
	// mlx_hook(data->win, ON_KEYDOWN, 0, on_key_down, data);
	// mlx_hook(data->win, ON_KEYUP, 0, on_key_up, data);
	// mlx_hook(data->win, ON_MOUSEMOVE, 0, handle_mouse, data);
	mlx_loop_hook(data->mlx, frame, data);
	mlx_loop(data->mlx);
	return (0);
}
