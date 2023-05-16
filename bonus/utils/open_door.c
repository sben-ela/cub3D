
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:29:57 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/24 15:06:13 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_strdup(const char *source)
{
	char	*mem;
	int		i;

	i = 0;
	mem = malloc((ft_strlen(source) + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	while (source[i] != '\0')
	{
		mem[i] = source[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

void	open_door(t_data *data)
{
	int	x;
	int	y;
	int	pid;

	x = data->player.x + data->player.dir_x;
	y = data->player.y + data->player.dir_y;
	if (data->map[y][x] != 'D' && data->map[y][x] != 'O')
		return ;
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'O';
	else
		data->map[y][x] = 'D';
	ft_voice("textures/open_door.mp3", &pid);
}

int	count_line_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		i++;
	}
	return (i);
}





// int	floud(char **map, int i, int j)
// {
// 	if (i <= 0 || i >= count_line_map(map) - 1 || j <= 0
// 		|| j >= ft_strlen(map[0]) - 1 || map[i][j] == '4' || map[i][j] == 'D' || map[i][j] == 'O')
// 		return (0);
// 	else
// 		map[i][j] = '4';
// 	floud(map, i + 1, j);
// 	floud(map, i - 1, j);
// 	floud(map, i, j + 1);
// 	floud(map, i, j - 1);
// 	return (1);
// }

// void	celing(t_data *data)
// {
// 	int i = 0;
// 	int j = 0;

// 	if (data->map[(int)data->player.y][(int)data->player.x] == '4')
// 	{
// 		while (i < WIDTH)
// 		{
// 			while (j < HEIGHT / 2)
// 			{
// 				ft_put_pixel(&data->img, i, j, ft_get_pixel(&data->celing_texture, i, j));
// 				j++;
// 			}
// 			i++;
// 		}
// 	}
// }