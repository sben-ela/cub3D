/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:46:10 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/29 00:36:58 by nbarakat         ###   ########.fr       */
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
# define FLOOR 0xf8c291
# define CEILING 0x70a1ff
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define GREY 0x00808080
# define NONE 0x463f3a
# define DOOR 1
# define WALL 0
# define LEFT 43
# define RIGHT 47
# define UP 126
# define DOWN 125
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4
# define FIRE 3
# define RELOAD 15
# define OPEN 49

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

enum			e_hook_type
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum			e_keys
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
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			direction;
}				t_player;

typedef struct s_hooks
{
	int			horizontal;
	int			vertical;
	int			rotation;
}				t_hooks;

typedef struct data
{
	t_hooks		hooks;
	t_player	player;
	t_img		img;
	t_img		texture[4];
	t_img		sprite;
	t_img		door;
	t_img		ceiling_texture;
	void		*mlx;
	void		*win;
	void		*fire;
	char		**map;
	void		*weapon[85];
	int			compass;
	double		speed;
	int			count;
	int			*position;
	int			floor;
	int			ceiling;
	int			fd;
	int			reload;
	int			flag;
	int			left_right;
	int			up_down;
	int			size;
	double		angle;
	int			last_x;
	double		last_y;
	int			hitted;
	int			over;
	int			pid;
	int			side;
	int			pos_x;
	int			pos_y;
	int			step_x;
	int			step_y;
	double		s_delta_x;
	double		s_delta_y;
	double		delta_x;
	double		delta_y;
	int			direction;
	char		**paths;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	double		start;
	double		end;
	double		x_prime;
	double		y_prime;
	int			skipped;
}				t_data;

typedef struct dist
{
	double		distance;
	double		wall_x;
	int			direction;
}				t_dist;

char			**ft_get_new_map(t_data *data, int i, int j, char **map);
void			get_direction(t_data *data);
void			fix_direction(t_data *data);
void			rotate(double *x_prime, double *y_prime, double angle);
void			draw_line(t_data *data, double ray_x, double ray_y, double len);
void			ft_putplayer(t_data *data, double x, double y, int color);
void			ft_putcube(t_data *data, int x, int y, int color);
void			draw_rays(t_data *data);
void			ft_voice(char *voice, pid_t *pid);
int				ft_get_pixel(t_img *img, int x, int y);
void			open_door(t_data *data);
void			draw_walls(t_data *data, double len, int x, double wallx);
void			draw_floor_and_ceiling(t_data *data);
void			ft_put_pixel(t_img *img, int x, int y, int rgb);
t_dist			dda(t_data *data, double ray_x, double ray_y);
void			get_player_pos(t_player *player, char **map);
int				frame(t_data *data);
void			new_image(t_data *data);
int				on_key_up(int keypress, t_data *data);
int				on_key_down(int keypress, t_data *data);
int				ft_strlen(const char *s);
char			*get_next_line(int fd);
int				count_line(char *av);
char			**get_map(int fd, int count);
int				handle_mouse(int x, int y, t_data *data);
void			draw_minimap(t_data *data, char **map, int x, int y);
int				mlx_mouse_move(void *win_ptr, int x, int y);
char			*ft_itoa(int n);
void			ft_destroy(t_data *data);
void			weapon(t_data *data);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
/*****************************/
void			error(void);
void			check_args(int ac, char *av[]);
void			check_file(char **map, t_data *data);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
int				get_index_(char *s, char **map);
char			*ft_strtrim(char const *s1, char const *set);
int				is_empty(char *s);
int				is_map_line(char *s);
void			double_free(char **s);
int				getmapsize(char **map, int index);
void			ft_strcpy(char *dst, const char *src);
void			check_characters(int *characters, char **map, int i);
void			check_colors(char **map, t_data *data);
void			check_walls(int index, char **map, t_data *data);
void			check_corners(char **map, int index, t_data *data);
void			copy_init(char **copy, char **map, int index, int largest);
int				get_largest(char **map, int index);
void			fill_characters(int *characters);
void			fill_space(char **copy, int largest, char **map, int index);
int				get_index(char **map);
void			check_elements(char **map);
void			check_doors(char **map);

#endif
