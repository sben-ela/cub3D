/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:24:13 by nbarakat          #+#    #+#             */
/*   Updated: 2023/05/28 02:52:15 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	ft_strncmp(const char	*str1, const char	*str2, size_t	n)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

void check_args(int ac, char    *av[])
{
    int     len;
    char    *cub;
    int     i;
    
    if (ac != 2)
        printf("Wrong number of argument !\n"), exit(1);
    i = 3;
    len = ft_strlen(av[1]);
    cub = ".cub";
    while (i != -1 && len != 0)
    {
        if (av[1][len - 1] != cub[i])
            printf("Wrong file extension !\n"), exit(1);
        i--;
        len--;
    }
}

void set_elements(char **s)
{
    s[0] = "NO ";
    s[1] = "SO ";
    s[2] = "WE ";
    s[3] = "EA ";
    s[4] = "F ";
    s[5] = "C ";
    s[6] = NULL;
}

int is_empty(char *s)
{
    int i;
    
    i = 0;
    while (s && s[i])
    {
        if (s[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int is_map_line(char    *s)
{
    int i;

    i = 0;
    if (s[0] == 0 || is_empty(s))
        return (0);
    while (s[i])
    {
        if (s[i] != '0' && s[i] != '1' && s[i] != ' '
            && s[i] != 'N' && s[i] != 'S' && s[i] != 'E'
            && s[i] != 'W' && s[i] != 'D')
                return (0);
        i++;
    }
    return (1);
}

void check_count(char  **map, char **elements)
{
    int i;
    int j;
    int count;

    j = 0;
    while (elements[j])
    {
        i = 0;
        count = 0;
        while (map[i] && !is_map_line(map[i]))
        {
            if (!ft_strncmp(map[i], elements[j], ft_strlen(elements[j])))
                count++;
            i++;
        }
        if (count != 1)
            printf("check elements on map file :(\n"), exit(1);
        j++;
    }
}

void check_path(char    **map, char **elements)
{
    int i;
    int index;

    i = 0;
    while (elements[i])
    {
        index = get_index_(elements[i], map);
        if (!map[index][2] || (map[index][2] && is_empty(&map[index][2])))
            printf("paths must be set :(\n"), exit(1);
        i++;
    }
}

void check_elements(char    **map)
{
    char    *elements[7];
    int     i;
    
    i  = 0;
    while (map[i])
    {
        if (!map[i][0] || is_empty(map[i]) || !ft_strncmp(map[i],"NO ", 3) 
            || !ft_strncmp(map[i],"SO ", 3) || !ft_strncmp(map[i],"WE ", 3) 
            || !ft_strncmp(map[i],"EA ", 3) || !ft_strncmp(map[i],"F ", 2)
            || !ft_strncmp(map[i],"C ", 2) || is_map_line(map[i]))
                i++;
        else
            printf("check elements on map file :(\n"), exit(1);    
    }
    set_elements(elements);
    check_count(map, elements);
    check_path(map, elements);
}

void fill_characters(int *characters)
{
    characters[0] = 0;
    characters[1] = 0;
    characters[2] = 0;
    characters[3] = 0;
    characters[4] = 0;
}

int get_index(char  **map)
{
    int i;
    
    i = 0;
    while (map[i])
    {
        if (is_map_line(map[i]))
            return (i);
        i++;
    }
    printf("check map file :(\n"), exit(1);
}

void check_chars(int *n)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (i < 4)
    {
        if (n[i] == 1)
            flag++;
        else if (n[i] != 0)
            printf("check map file :(\n"), exit(1);
        i++;
    }
    if (flag != 1)
        printf("check map file :(\n"), exit(1);
}

void check_characters(int   *characters, char  **map, int i)
{
    int l;
    
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

void check_num(char **s, t_data  *data, int flag)
{
    int num;
    int i;
    
    i = 0;
    while (i < 3)
    {
        num = ft_atoi(s[i]);
        if (num < 0 || num > 255)
            printf("R,G,B colors in range [0,255]: 0, 255, 255\n"), exit(1);
        i++;
    }
    if (flag == 1)
        data->floor = (ft_atoi(s[0]) << 16) | (ft_atoi(s[1]) << 8) | (ft_atoi(s[2]));
    else if (flag == 0)
        data->ceiling = (ft_atoi(s[0]) << 16) | (ft_atoi(s[1]) << 8) | (ft_atoi(s[2]));
        
}

void double_free(char   **s)
{
    int i;
    
    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
     free(s);
}

void check_rgb(char **map, int i, t_data    *data, int flag)
{
    int j;
    char    **split1 = NULL;

    j = 1;
    while (map[i][j] && map[i][j] == ' ')
        j++;
    if (map[i][j])
    {
        split1 = ft_split(&map[i][j], ',');
        if (!split1 || !split1[0] || !split1[1] || !split1[2] || split1[3])
            printf("R,G,B colors in range [0,255]: 0, 255, 255\n"), exit(1);
        if (split1 && split1[0])
            check_num(split1, data, flag);
        double_free(split1);
    }
    else
        printf("R,G,B colors in range [0,255]: 0, 255, 255\n"), exit(1);

}

void check_colors(char **map, t_data *data)
{
    int i;

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

void check_first(char   **map, int index)
{
    int i;

    i = 0;
    while (map[index][i])
    {
        if (map[index][i] != '1' && map[index][i] != ' ')
            printf("The map must be surrounded by walls\n"), exit(1);
        i++;
    }
}

void check_last(char    **map, int index)
{
    int i;

    i = 0;
    while (map[index] && !is_empty(map[index])) 
        index++;
    index--;
     while (map[index][i])
    {
        if (map[index][i] != '1' && map[index][i] != ' ')
            printf("The map must be surrounded by walls\n"), exit(1);
        i++;
    }
}

void check_otherside(char   *line)
{
    int i;

    i = ft_strlen(line);
    while (line[i - 1] == ' ')
        i--;
    if (line[i - 1] != '1')
        printf("The mapy must be surrounded by walls\n"), exit(1);

}

void check_sides(char   **map, int index)
{
    int i;

    while (map[index] && !is_empty(map[index]))
    {
        i = 0;
        while (map[index][i])
        {
            while (map[index][i] == ' ')
                i++;
            if (map[index][i] != '1')
                printf("The map must be surrounded by walls\n"), exit(1);
            check_otherside(map[index]);
            break ;
        }
        index++;
    }
}

int getmapsize(char **map, int index)
{
    int size;

    size = 1;
    while (map[index] && !is_empty(map[index]))
    {
        index++;
        size++;
    }
    return (size);
}

int get_largest(char    **map, int index)
{
    int ret;
    
    ret = index;
    while (map[index])
    {
        if (ft_strlen(map[index]) > ft_strlen(map[ret]))
            ret  = index;
        index++;
    }
    return (ft_strlen(map[ret]));
}

void fill_space(char    **copy, int largest, char   **map, int index)
{
    int i;
    int j;

    i = 0;
    while (i < getmapsize(map, index) - 1)
    {
        copy[i] = malloc ((largest + 1) * sizeof (char));
        j = 0;
        while (j < largest)
        {
            copy[i][j] = ' ';
            j++;
        }
        copy[i][j] = 0;
        i++;
    }
    copy[i] = 0;
}

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void copy_init(char **copy, char    **map, int index, int largest)
{
    int i;
    int size;

    i = 0;
    size = getmapsize(map, index) - 1;
    fill_space(copy, largest, map, index);
    while (i < size)
    {
        ft_strcpy(copy[i], map[index]);
        i++;
        index++;
    }
}

void corners(char   **map)
{
    int i;
    int j;

    i = 1;
    while (map[i])
    {
        j = 1;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
                j++;
            else if ((map[i - 1][j] == ' ' || map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' '
                    || (map[i + 1] && map[i + 1][j] == ' ') || (map[i + 1] && map[i + 1][j - 1] == ' ')
                    || (map[i + 1] && map[i + 1][j + 1] == ' ') || map[i][j + 1] == ' ' || map[i][j - 1] == ' ') 
                    && map[i][j] != '1')
                    printf("Map invalid :(\n"), exit(1);
            else
                j++;
        }
        i++;
    }
}

void set_textures(char  **s)
{
    s[0] = "NO";
    s[1] = "SO";
    s[2] = "WE";
    s[3] = "EA";
    s[4] = NULL;
}

void set_paths(t_data   *data, char **map)
{
    int     i;
    char    *ptr;
    char    *textures[5];
    char    *path;

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


void check_corners(char **map, int index, t_data *data)
{

    char    **copy;
    int     largest;

    data->size = getmapsize(map, index);
    largest =  get_largest(map, index);
    copy = malloc(data->size * sizeof(char    *));
    copy_init(copy, map, index, largest);
    corners(copy);
    set_paths(data, map);
    double_free(map);
    data->map = copy;
    /*****************************************/
}

void check_walls(int index, char    **map, t_data *data)
{
    check_first(map, index);
    check_last(map, index);
    check_sides(map, index);
    check_corners(map, index, data);
}

void check_newline(char **map, int  index)
{
    int flag;

    flag = 0;
    while (map[index])
    {
        if (map[index][0] == 0)
        {
            flag = 1;
            break ;
        }   
        index++;
    }
    if (flag)
    {
        while (map[index])
        {
            if (!is_empty(map[index]))
                printf("Map content can't  have  a newline\n"), exit(1);
            index++;
        }
    }
}

void check_map(char **map, t_data *data)
{
    int     characters[5];
    int     index;

    index = get_index(map);
    fill_characters(characters);
    check_characters(characters, map, index);
    check_newline(map, index);
    check_walls(index, map, data);
}


void check_doors(char   **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'D')
                return ;
            j++;
        }
        i++;
    }
    printf("Doors needed in map :(\n"), exit(1);
}

void check_file(char  **map, t_data *data)
{
    check_elements(map);
    check_colors(map, data);
    check_map(map, data);
    check_doors(data->map);
}
