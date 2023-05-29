/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:24:13 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/28 00:21:58 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_args(int ac, char *av[])
{
	int		len;
	char	*cub;
	int		i;

	if (ac != 2)
	{
		printf("Wrong number of argument !\n");
		exit(1);
	}
	i = 3;
	len = ft_strlen(av[1]);
	cub = ".cub";
	while (i != -1 && len != 0)
	{
		if (av[1][len - 1] != cub[i])
		{
			printf("Wrong file extension !\n");
			exit(1);
		}
		i--;
		len--;
	}
}

void	check_newline(char **map, int index)
{
	int	flag;

	flag = 0;
	while (map[index])
	{
		if (map[index][0] == 0 || is_empty(map[index]))
		{
			flag = 1;
			break ;
		}
		index++;
	}
	if (flag == 1)
	{
		while (map[index])
		{
			if (!is_empty(map[index]))
			{
				printf("Map content can't  have  a newline\n");
				exit(1);
			}
			index++;
		}
	}
}

void	check_map(char **map, t_data *data)
{
	int	characters[5];
	int	index;

	index = get_index(map);
	fill_characters(characters);
	check_characters(characters, map, index);
	check_newline(map, index);
	check_walls(index, map, data);
}

void	check_file(char **map, t_data *data)
{
	check_elements(map);
	check_colors(map, data);
	check_map(map, data);
	check_doors(data->map);
}
