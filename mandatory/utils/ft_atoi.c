/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:25:48 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/21 20:36:24 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static long	ft_check(char	*str)
{
	long	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	return (i);
}

void	is_number(const char *s)
{
    int i;
    
    i = 0;
    while (s[i])
    {
        if (s[i] >= '0' && s[i] <= '9')
            i++;
        else
            printf("R,G,B colors in range [0,255]: 0, 255, 255\n"), exit(1);

    }
}

int	ft_atoi(const char	*str)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = ft_check((char *)str);
    is_number(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result < 0 && sign > 0)
		return (-1);
	if (result < 0 && sign < 0)
		return (0);
	return (sign * result);
}