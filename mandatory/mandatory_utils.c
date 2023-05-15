#include "cub.h"

void get_player_pos(t_player *player, char **map)
{
	int 	i;
	int 	j;
	char	*line;

	i = 0;
	while(map[i])
	{
		j = 0;
		line = map[i];
		while(line[j])
		{
			if (line[j] == 'N')
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	count_line(char *av)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(av, O_RDWR);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (i);
}

char	**get_map(int fd, int count)
{
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		exit(0);
	while (i < count)
	{
		map[i] = get_next_line(fd);
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = 0;
		i++;
	}
	map[i] = 0;
	return (map);
}

void	new_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
	&data->img.size_line, &data->img.endian);
}

void    ft_destroy(t_data *data)
{
	kill(data->pid, SIGKILL);
    mlx_destroy_window(data->mlx, data->win);
    exit (0);
}

void	weapondire(int keypress, t_data *data)
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