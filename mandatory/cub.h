/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:37:10 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/29 00:03:53 by nbarakat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define HEIGHT 1000
# define WIDTH 1000
# define TRANS_SPEED 0.15
# define ROT_ANGLE 0.1
# define CELL_SIZE 10
# define PLAYER_SIZE 5
# define HOR 0
# define VER 1
# define FLOOR	0xf8c291
# define CEILING	0x70a1ff
# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define RED		0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define YELLOW 	0x00FFFF00
# define GREY 	0x00808080
# define NONE	0x463f3a
# define DOOR	1
# define WALL	0
# define LEFT	43
# define RIGHT	47
# define UP		126
# define DOWN	125
# define NORTH	1
# define SOUTH	2
# define EAST	3
# define WEST	4
# define FIRE	3
# define RELOAD	15
# define OPEN	49

# include	<stdlib.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<fcntl.h>
# include	<string.h>
# include	<math.h>
# include	"mlx.h"

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
	ESC = 53,
	KEY_A = 0,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_W = 13,
	KEY_S = 1,
	KEY_D = 2
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		direction;
}	t_player;

typedef struct s_hooks
{
	int	horizontal;
	int	vertical;
	int	rotation;
}	t_hooks;

typedef struct door
{
	double	distance;
	int		x;
	int		y;
	int		flag;
	double	dir_x;
	double	dir_y;
}	t_door;

typedef struct data
{
	void		*mlx;
	void		*win;
	char		**map;
	t_hooks		hooks;
	t_player	player;
	t_img		img;
	t_img		texture[4];
	int			compass;
	int			count;
	int			floor;
	int			ceiling;
	int			fd;
	double		angle;
	int			side;
	int			pos_x;
	int			pos_y;
	int			step_x;
	int			step_y;
	double		s_delta_x;
	double		s_delta_y;
	double		delta_x;
	double		delta_y;
	double		start;
	double		end;
	double		x_prime;
	double		y_prime;
	int			direction;
	char		**paths;
	char		**new_map;
	int			size;
}	t_data;

typedef struct dist
{
	double	distance;
	double	wall_x;
	int		direction;
}	t_dist;

void		ft_error(char *error);
void		rotate(double *x_prime, double *y_prime, double angle);
char		*ft_join(char *left_str, char *buff);
char		*ft_strchr(const char *s, int c);
int			ft_get_pixel(t_img *img, int x, int y);
void		draw_walls(t_data *data, double len, int x, double wallx);
void		draw_floor_and_ceiling(t_data *data);
void		ft_put_pixel(t_img *img, int x, int y, int rgb);
t_dist		dda(t_data *data, double ray_x, double ray_y);
void		get_player_pos(t_player *player, char **map);
int			frame(t_data *data);
void		new_image(t_data *data);
int			on_key_up(int keypress, t_data *data);
int			on_key_down(int keypress, t_data *data);
int			ft_strlen(const char *s);
char		*get_next_line(int fd);
int			count_line(char *av);
char		**get_map(int fd, int count);
void		draw_rays(t_data *data);
void		draw_line(t_data *data, double ray_x, double ray_y, double len);
void		ft_destroy(t_data *data);
/*****************************/
void		error(void);
void		check_args(int ac, char *av[]);
void		check_file(char **map, t_data *data);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char	*str);
int			ft_strncmp(const char	*str1, const char	*str2, size_t	n);
int			get_index_(char *s, char **map);
char		*ft_strtrim(char const	*s1, char const	*set);
int			is_empty(char *s);
int			is_map_line(char *s);
void		double_free(char **s);
int			getmapsize(char **map, int index);
void		ft_strcpy(char *dst, const char *src);
void		check_characters(int *characters, char **map, int i);
void		check_colors(char **map, t_data *data);
void		check_walls(int index, char **map, t_data *data);
void		check_corners(char **map, int index, t_data *data);
void		copy_init(char **copy, char **map, int index, int largest);
int			get_largest(char **map, int index);
void		fill_characters(int *characters);
void		fill_space(char **copy, int largest, char **map, int index);
int			get_index(char **map);
void		check_elements(char **map);
#endif
