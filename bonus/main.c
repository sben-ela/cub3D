#include "cub.h"

void	init_weapon(t_data *data)
{
	int i;
	int hight, width;
	static char	reload[85][15] = {"weapon/1.xpm", "weapon/2.xpm", "weapon/3.xpm", "weapon/4.xpm", "weapon/5.xpm", "weapon/6.xpm"
		, "weapon/7.xpm", "weapon/8.xpm", "weapon/9.xpm", "weapon/10.xpm", "weapon/11.xpm", "weapon/12.xpm", "weapon/13.xpm"
		, "weapon/14.xpm", "weapon/15.xpm", "weapon/16.xpm", "weapon/17.xpm", "weapon/18.xpm", "weapon/19.xpm", "weapon/20.xpm"
		, "weapon/21.xpm", "weapon/22.xpm", "weapon/23.xpm", "weapon/24.xpm", "weapon/25.xpm", "weapon/26.xpm", "weapon/27.xpm"
		, "weapon/28.xpm", "weapon/29.xpm", "weapon/30.xpm", "weapon/31.xpm", "weapon/32.xpm", "weapon/33.xpm", "weapon/34.xpm"
		, "weapon/35.xpm", "weapon/36.xpm", "weapon/37.xpm", "weapon/38.xpm", "weapon/39.xpm", "weapon/40.xpm", "weapon/41.xpm"
		, "weapon/42.xpm", "weapon/43.xpm", "weapon/44.xpm", "weapon/45.xpm", "weapon/46.xpm", "weapon/47.xpm", "weapon/48.xpm"
		, "weapon/49.xpm", "weapon/50.xpm", "weapon/51.xpm", "weapon/52.xpm", "weapon/53.xpm", "weapon/54.xpm", "weapon/55.xpm"
		, "weapon/56.xpm", "weapon/57.xpm", "weapon/58.xpm", "weapon/59.xpm" ,  "weapon/60.xpm", "weapon/61.xpm", "weapon/62.xpm"
		, "weapon/63.xpm", "weapon/64.xpm", "weapon/66.xpm", "weapon/66.xpm", "weapon/67.xpm", "weapon/68.xpm", "weapon/69.xpm"
		, "weapon/70.xpm", "weapon/71.xpm", "weapon/72.xpm", "weapon/73.xpm", "weapon/74.xpm", "weapon/75.xpm", "weapon/76.xpm"
		, "weapon/77.xpm", "weapon/78.xpm", "weapon/79.xpm", "weapon/80.xpm", "weapon/81.xpm", "weapon/82.xpm", "weapon/83.xpm"
		, "weapon/84.xpm"};

	i = 0;
	while (i < 84)
	{
		data->weapon[i] = mlx_xpm_file_to_image(data->mlx, reload[i], &width, &hight);
		if (i % 10 == 0)
			printf("\033[0;32m waiting ...\033[0m\n");
		i++;
	}
	data->weapon[i] = 0;
}

void	init_textures(t_data *data)
{
	int hight, width;
	char *paths[4] = {"textures/wall5.xpm", "textures/wall2.xpm", "textures/wall.xpm", "textures/wall3.xpm"};
	data->door.img = mlx_xpm_file_to_image(data->mlx, "textures/door_1.xpm", &data->door.width, &data->door.height);
	data->door.addr = mlx_get_data_addr(data->door.img, &data->door.bpp, &data->door.size_line, &data->door.endian);
	int i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, paths[i], &data->texture[i].width, &data->texture[i].height);
		if (!data->texture[i].img)
			exit (EXIT_FAILURE);
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img, &data->texture[i].bpp, &data->texture[i].size_line, &data->texture[i].endian);
		if (!data->texture[i].addr)
			exit (EXIT_FAILURE);
		i++;
	}
	data->fire = mlx_xpm_file_to_image(data->mlx, "weapon/fire.xpm", &width, &hight);
	init_weapon(data);
}

void    init_data(t_data *data, char *map)
{
	data->ceiling = CEILING;
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
	data->mouse_y = HEIGHT / 2;
	data->mouse_x = WIDTH / 2;
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
	mlx_hook(data->win, ON_MOUSEMOVE, 0, handle_mouse, data);
	mlx_loop_hook(data->mlx, frame, data);
	ft_voice("textures/player.mp3", &data->pid);
	mlx_loop(data->mlx);
	return (0);
}
