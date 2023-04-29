#include "cub.h"

int	player(int keypress, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keypress == 1)
	{
		if (data->w == HEIGHT)
		{
			data->w = HEIGHT / 2;
			return (0);
		}
		data->w = HEIGHT;
	}
	return (0);
}


void    init_data(t_data *data, char *map)
{
	data->celing = CELING;
	data->floor = FLOOR;
	data->fd = open(map, O_RDONLY);
	if (data->fd < 0)
		printf("bad file discriptor :)\n"), exit (1);
	data->count = count_line(map);
	data->map = get_map(data->fd, data->count);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	get_player_pos(&data->player, data->map);
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.65;
	data->player.plane_y = 0;
	data->hooks.horizontal = -1;
	data->hooks.vertical = -1;
	data->hooks.rotation = -1;
	data->sdoor.x = -1;
	data->sdoor.y = -1;
	data->w = HEIGHT;
	data->door.img = mlx_xpm_file_to_image(data->mlx, "textures/door_1.xpm", &data->door.width, &data->door.height);
	data->door.addr = mlx_get_data_addr(data->door.img, &data->door.bpp, &data->door.size_line, &data->door.endian);
	data->texture.img = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm", &data->texture.width, &data->texture.height);
	data->texture.addr = mlx_get_data_addr(data->texture.img, &data->texture.bpp, &data->texture.size_line, &data->texture.endian);
}

int	main(int ac, char **av)
{
	t_data *data;

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
