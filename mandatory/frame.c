/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:05:49 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/14 21:47:31 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_put_pixel(t_img *img, int x, int y, int rgb)
{
	int	offset;
	int	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	offset = x * img->bpp / 8 + img->size_line * y;
	dst = (int *)(img->addr + offset);
	*dst = rgb; 
}

int frame(t_data *data)
{
	data->sdoor.distance = -1;
	data->sdoor.flag = 0;
    new_image(data);
	draw_floor_and_celing(data);
	// draw_rays(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.img);
    return (0);
}
