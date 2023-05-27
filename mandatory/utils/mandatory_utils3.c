/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:13:23 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/27 15:30:09 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_get_pixel(t_img *img, int x, int y)
{
	int	offset;
	int	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	offset = (x * img->bpp / 8) + img->size_line * y;
	dst = (int *)(img->addr + offset);
	return (*dst);
}

void	ft_error(char *error)
{
	printf("%s\n", error);
	exit (EXIT_FAILURE);
}

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
