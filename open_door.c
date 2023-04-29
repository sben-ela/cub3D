#include "cub.h"

void	open_door(t_data *data)
{
	int	x;
	int	y;

	x = data->player.x + data->player.dir_x;
	y = data->player.y + data->player.dir_y;
	if (data->map[y][x] != 'D' && data->map[y][x] != 'O')
		return ;
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'O';
	else
		data->map[y][x] = 'D';
}