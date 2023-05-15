/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:14:05 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/15 09:40:08 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

void	ft_voice(char *voice,  pid_t *pid)
{
	static char *command[3] = {"afplay", 0, 0};
	command[1] = voice;
	
	*pid = fork();
	if (!*pid)
		execve("/usr/bin/afplay", command, 0);	
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

	if (x < 0 || x >= WIDTH)
	{
		pos_x = 0;
		if (x < 0)
			pos_x = WIDTH - 1;
		mlx_mouse_move(data->win, pos_x, y);
		data->mouse_x = pos_x;
		x = pos_x;
	}
	if (y - data->mouse_y > 0)
		data->up_down -= 2;
	else
		data->up_down += 2;
	data->mouse_y = y;
	dx = x - data->mouse_x;
	data->angle = (-dx * M_PI) / WIDTH;
	data->mouse_x = x;
	return (0);
}
