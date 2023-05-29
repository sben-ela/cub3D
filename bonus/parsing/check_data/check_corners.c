/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_corners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:29:55 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/29 00:13:09 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	error_corner(void)
{
	printf("Map invalid :(\n");
	exit(1);
}

void	corners(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				j++;
			else if ((map[i - 1][j] == ' ' || map[i - 1][j - 1] == ' '
				|| map[i - 1][j + 1] == ' ' || (map[i + 1]
				&& map[i + 1][j] == ' ') || (map[i + 1]
				&& map[i + 1][j - 1] == ' ') || (map[i + 1]
				&& map[i + 1][j + 1] == ' ') || map[i][j + 1] == ' '
				|| map[i][j - 1] == ' ') && map[i][j] != '1')
				error_corner();
			else
				j++;
		}
		i++;
	}
}

void	set_textures(char **s)
{
	s[0] = "NO";
	s[1] = "SO";
	s[2] = "EA";
	s[3] = "WE";
	s[4] = NULL;
}

void	set_paths(t_data *data, char **map)
{
	int		i;
	char	*ptr;
	char	*textures[5];
	char	*path;

	i = 0;
	set_textures(textures);
	data->paths = malloc(5 * sizeof(char *));
	data->paths[4] = NULL;
	while (i < 4)
	{
		ptr = map[get_index_(textures[i], map)];
		path = ft_strtrim(&ptr[2], " ");
		data->paths[i] = malloc(ft_strlen(path) + 1);
		ft_strcpy(data->paths[i], path);
		i++;
		free(path);
	}
}

void	check_corners(char **map, int index, t_data *data)
{
	char	**copy;
	int		largest;

	data->size = getmapsize(map, index);
	largest = get_largest(map, index);
	copy = malloc(data->size * sizeof(char *));
	copy_init(copy, map, index, largest);
	corners(copy);
	set_paths(data, map);
	double_free(map);
	data->map = copy;
}
