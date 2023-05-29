/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:19:09 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/27 23:20:39 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_num(char **s, t_data *data, int flag)
{
	int	num;
	int	i;

	i = 0;
	while (i < 3)
	{
		num = ft_atoi(s[i]);
		if (num < 0 || num > 255)
		{
			printf("R,G,B colors in range [0,255]: 0, 255, 255\n");
			exit(1);
		}
		i++;
	}
	if (flag == 1)
		data->floor = (ft_atoi(s[0]) << 16) | (ft_atoi(s[1]) << 8)
			| (ft_atoi(s[2]));
	else if (flag == 0)
		data->ceiling = (ft_atoi(s[0]) << 16) | (ft_atoi(s[1]) << 8)
			| (ft_atoi(s[2]));
}

void	check_rgb(char **map, int i, t_data *data, int flag)
{
	int		j;
	char	**split1;

	split1 = NULL;
	j = 1;
	while (map[i][j] && map[i][j] == ' ')
		j++;
	if (map[i][j])
	{
		split1 = ft_split(&map[i][j], ',');
		if (!split1 || !split1[0] || !split1[1] || !split1[2] || split1[3])
		{
			printf("R,G,B colors in range [0,255]: 0, 255, 255\n");
			exit(1);
		}
		if (split1 && split1[0])
			check_num(split1, data, flag);
		double_free(split1);
	}
	else
	{
		printf("R,G,B colors in range [0,255]: 0, 255, 255\n");
		exit(1);
	}
}

void	check_colors(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'F')
			check_rgb(map, i, data, 1);
		else if (map[i][0] == 'C')
			check_rgb(map, i, data, 0);
		i++;
	}
}
