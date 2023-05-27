/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:52:55 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/23 21:00:23 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int    get_index_(char  *s, char    **map)
{
    int i;
    
    i = 0;
    while (map[i])
    {
        if (!ft_strncmp(map[i], s, ft_strlen(s)))
            return (i);
        i++;
    }
    return (0);
}

void set_start_pos(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'W')
                data->direction = WEST;
            if (data->map[i][j] == 'S')
                data->direction = SOUTH;
            if (data->map[i][j] == 'E')
                data->direction = EAST;
            if (data->map[i][j] == 'N')
                data->direction = NORTH;
            j++;
        }
        i++;
    }
}

void set_data(t_data    *data)
{
    set_start_pos(data);
}