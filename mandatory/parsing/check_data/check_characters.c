/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:23:50 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/27 23:46:31 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	check_chars(int *n)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < 4)
	{
		if (n[i] == 1)
			flag++;
		else if (n[i] != 0)
		{
			printf("check map file :(\n");
			exit(1);
		}
		i++;
	}
	if (flag != 1)
	{
		printf("check map file :(\n");
		exit(1);
	}
}

void	check_characters(int *characters, char **map, int i)
{
	int	l;

	l = 0;
	while (map[i])
	{
		l = 0;
		while (map[i][l])
		{
			if (map[i][l] == 'N')
				characters[0] += 1;
			if (map[i][l] == 'W')
				characters[1] += 1;
			if (map[i][l] == 'E')
				characters[2] += 1;
			if (map[i][l] == 'S')
				characters[3] += 1;
			l++;
		}
		i++;
	}
	check_chars(characters);
}
