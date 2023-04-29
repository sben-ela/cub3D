#include "cub.h"


t_dist dda(t_data *data, double ray_x, double ray_y, int flag)
{
	t_dist dist;
	int		pos_x;
	int		pos_y;
	double	s_delta_x;
	double	s_delta_y;
	double	delta_x;
	double	delta_y;
	double	distance;
	int		step_x;
	int		step_y;
	int		side;

	step_x = -1;
	step_y = -1;
	pos_x = (int)data->player.x;
	pos_y = (int)data->player.y;
	distance = 0;
	s_delta_x = 1.0 / fabs(ray_x);
	s_delta_y = 1.0 / fabs(ray_y);
	delta_x = ((int)data->player.x + 1 - data->player.x) * s_delta_x;
	delta_y = ((int)data->player.y + 1 - data->player.y) * s_delta_y;
	if (ray_x < 0)
		delta_x = (data->player.x - (int)data->player.x) * s_delta_x;
	if (ray_y < 0)
		delta_y = (data->player.y - (int)data->player.y) * s_delta_y;
	if (ray_x > 0)
		step_x = 1;
	if (ray_y > 0)
		step_y = 1;
	while (1)
	{
		if (delta_x < delta_y)
		{
			delta_x += s_delta_x;
			pos_x += step_x;
			side = VER;
		}
		else
		{
			delta_y += s_delta_y;
			pos_y += step_y;
			side = HOR;
		}
		if (data->map[pos_y][pos_x] == '1' || data->map[pos_y][pos_x] == 'D')
		{
			data->hitted = DOOR - (data->map[pos_y][pos_x] == '1');
			distance = delta_y - s_delta_y;
			dist.wall_x = data->player.x + (distance * ray_x) / sqrt(pow(ray_x, 2) + pow(ray_y, 2));
			dist.wall_x -= (int)dist.wall_x;
			if (side == VER)
			{
				distance = delta_x - s_delta_x;
				dist.wall_x = data->player.y + (distance * ray_y) / sqrt(pow(ray_x, 2) + pow(ray_y, 2));
				dist.wall_x -= (int)dist.wall_x;
			}
			if (data->map[pos_y][pos_x] == 'D')
			{
				data->sdoor.x = pos_x;
				data->sdoor.y = pos_y;
				data->sdoor.distance = distance;
			}
			break ;
		}
		(void)flag;
	}
	dist.distance = distance;
	return(dist);
}















































// t_dist dda(t_data *data, double ray_x, double ray_y)
// {
// 	t_dist	dist;
// 	double 	distance;
// 	int		side;
// 	int 	pos_x;
// 	int 	pos_y;
// 	double 	delta_x;
// 	double 	delta_y;
// 	double 	s_delta_x;
// 	double 	s_delta_y;
// 	int 	step_x;
// 	int 	step_y;
	
// 	distance = 0;
// 	pos_x = (int)data->player.x;
// 	pos_y = (int)data->player.y;
// 	// step how bach ghadi n3erfo wach khasno nzido wla n9so mn l pos_x or l pos_y
// 	step_x = -1;
// 	step_y = -1;
// 	s_delta_x = 1.0 / fabs(ray_x);
// 	s_delta_y = 1.0 / fabs(ray_y);
// 	delta_x = ((int)data->player.x + 1 - data->player.x) * s_delta_x;
// 	delta_y = ((int)data->player.y + 1 - data->player.y) * s_delta_y;
// 	if (ray_x < 0)
// 		delta_x = (data->player.x - (int)data->player.x) * s_delta_x;
// 	if (ray_y < 0)
// 		delta_y = (data->player.y - (int)data->player.y) * s_delta_y;
// 	if (ray_x > 0)
// 		step_x = 1;
// 	if (ray_y > 0)
// 		step_y = 1;
// 	while (1)
// 	{
// 		if (delta_x < delta_y)
// 		{
// 			delta_x += s_delta_x;
// 			side = VER;
// 			pos_x += step_x;
// 		}
// 		else
// 		{
// 			delta_y += s_delta_y;
// 			side = HOR;
// 			pos_y += step_y;
// 		}
// 		if (data->map[pos_y][pos_x] == '1')
// 		{
// 			distance = delta_y - s_delta_y;
// 			dist.wall_x = data->player.x + ((distance * ray_x) / sqrt(pow(ray_x, 2) + pow(ray_y, 2)));
// 			dist.wall_x -= (int)dist.wall_x;
// 			if (side == VER)
// 			{
// 				distance = delta_x - s_delta_x;
// 				dist.wall_x = data->player.y + ((distance * ray_y) / sqrt(pow(ray_x, 2) + pow(ray_y, 2)));
// 				dist.wall_x -= (int)dist.wall_x;
// 			}
// 			break ;
// 		}
// 	}
// 	dist.distance = distance;
// 	return (dist);
// }