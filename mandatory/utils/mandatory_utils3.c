#include "../cub.h"

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

void	ft_error(char *error)
{
	printf("%s\n", error);
	exit (EXIT_FAILURE);
}