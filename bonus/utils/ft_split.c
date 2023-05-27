/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:54:53 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/21 20:41:36 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	ft_countwords(const char *str, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			i++;
			j = 1;
		}
		if (j == 1)
			k++;
	}
	return (k);
}

size_t	ft_strlcpy(char	*dst, const char *src, size_t	size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(src);
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (length);
}

static void	ft_position(const char *s, int *i, int *len, char c)
{
	while (s[(*i)] && s[(*i)] == c)
		(*i)++;
	*len = *i;
	while (s[(*len)] && s[(*len)] != c)
		(*len)++;
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	ptr = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		ft_position(s, &i, &len, c);
		if (s[i] && s[i] != c)
		{
			ptr[j] = malloc((len - i + 1) * sizeof (char));
			ft_strlcpy (ptr[j++], s + i, len - i + 1);
		}
        else 
            printf("error\n"), exit(1);
		i = len;
	}
	ptr[j] = NULL;
	return (ptr);
}