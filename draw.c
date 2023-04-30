#include "cub.h"

void draw_floor_and_celing(t_data *data)
{
    int i;
    int j;
    int color;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        color = data->celing;
		if (data->map[(int)data->player.y][(int)data->player.x] == '4')
			color = GREY;
        while (j < HEIGHT)
        {
            if (j > HEIGHT / 2)
                color = data->floor;
            ft_put_pixel(&data->img, i, j, color);
            j++;
        }
        i++;
    }    
}

int	ft_get_pixel(t_img *img, int x, int y)
{
	int	offset;
	int	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return 0;
	offset = x * img->bpp / 8 + img->size_line * y;
	dst = (int *)(img->addr + offset);
	return (*dst);
}

void	draw_walls(t_data *data, double len, int x, double wallx)
{
	double	start;
	double	end;
    double	x_prime;
	double	y_prime;
	t_img	*texture;
	int		skipped;
	int		i;

	texture = &data->texture;
	if (data->hitted == DOOR)
		texture = &data->door;
	skipped = 0;
	start = HEIGHT / 2 - len / 2;
	end = HEIGHT / 2 + len / 2;
	if (start < 0)
	{
		skipped = -start;
		start = 0;
	}
	if (end > HEIGHT)
		end = HEIGHT;
    i = 0;
    x_prime = data->texture.width * wallx;
	while (start + i < end)
	{
		y_prime = (double)((double)(i + skipped) / len) * data->texture.height;
		ft_put_pixel(&data->img, x, start + i, ft_get_pixel(texture, x_prime, y_prime));
        i++;
	}
}
