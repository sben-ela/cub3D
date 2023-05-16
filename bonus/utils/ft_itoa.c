/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 07:39:48 by aybiouss          #+#    #+#             */
/*   Updated: 2023/05/05 15:13:53 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_length(int n)
{
	int		count;
	long	num;

	num = n;
	count = 1;
	if (n < 0)
	{
		num = -num;
		count++;
	}
	else if (num == 0)
		return (1);
	while (num > 9)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*mem;
	unsigned long	num;
	int				i;

	num = n;
	i = ft_length(n);
	mem = malloc(i + 1);
	if (!mem)
		return (NULL);
	if (n < 0)
	{
		mem[0] = '-';
		num = -num;
	}
	mem[i--] = '\0';
	if (num == 0)
		mem[i] = '0';
	while (i >= 0 && num != 0)
	{
		mem[i--] = '0' + num % 10;
		num /= 10;
	}
	return (mem);
}
