/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:46:10 by sben-ela          #+#    #+#             */
/*   Updated: 2023/05/09 11:19:47 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	CUB_H
# define	CUB_H

# define	HEIGHT 1000
# define	WIDTH 1000
# define	TRANS_SPEED 0.15
# define	ROT_ANGLE 0.1
# define	CELL_SIZE 10
# define	PLAYER_SIZE 5
# define	HOR 0
# define	VER 1
# define	FLOOR	0xf8c291
# define	CELING	0x70a1ff
# define 	WHITE	0x00FFFFFF
# define 	BLACK	0x00000000
# define	RED		0x00FF0000 
# define	GREEN	0x0000FF00
# define	BLUE	0x000000FF
# define	YELLOW 	0x00FFFF00
# define	GREY 	0x00808080
# define	NONE	0x463f3a
# define	DOOR	1
# define	WALL	0
# define	LEFT	43
# define	RIGHT	47
# define	UP		126
# define	DOWN	125
# define	NORTH	1
# define	SOUTH	2
# define	EAST	3
# define	WEST	4
# define	FIRE	3
# define	RELOAD	15
# define	OPEN	49

#include	<signal.h>
#include	<pthread.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<fcntl.h>
# include	<string.h>
# include	<math.h>
# include	"mlx.h"

enum e_hook_type {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_keys
{
	ESC = 53,
	KEY_A = 0,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_W = 13,
	KEY_S = 1,
	KEY_D = 2
};

typedef struct	s_img {
	void	*img;		// Pointer to the beginning of the image data
	char	*addr;		// Pointer to the beginning of the address data
	int		bpp;		// The number of bits used to represent each pixel in the image
	int		size_line;	// The number of bytes used to store one line of the image
	int		endian;		// The endianness of the image data (0 for little-endian, 1 for big-endian)
	int		width;
	int		height;
}   t_img;

typedef struct s_player
{
    double  x;
    double  y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}   t_player;

typedef	struct s_hooks
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
} t_door;

typedef struct data
{
    void 	    *mlx;
    void	    *win;
	void		*fire;
    char	    **map;
	void		*weapon[85];
	t_hooks		hooks;
    t_player    player;
    t_img       img; 
    t_img       texture[4];
	t_img		sprite;
	t_img		door;
	t_img		celing_texture;
	int			side;
	int			compass;
	double		speed;
    int		    count;
    int         *position;
	int			floor;
	int			celing;
	int			fd;
	int			reload;
	int			flag;
	int			left_right;
	int			up_down;
	int			w;
	double		angle;
	int			mouse_x;
	double		mouse_y;
	int			mouse;
	int			keypress;
	int			start;
	t_door		sdoor;
	int			hitted;
	int			over;
	pid_t		pid;
}   t_data;

typedef struct dist
{
	double	distance;
	double 	wall_x;
	int		direction;
} t_dist;

void		ft_voice(char *voice,  pid_t *pid);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
char		*ft_join(char *left_str, char *buff);
int			ft_get_pixel(t_img *img, int x, int y);
void		open_door(t_data *data);
void		draw_walls(t_data *data, double len, int x, double wallx);
void		draw_floor_and_celing(t_data *data);
void		ft_put_pixel(t_img *img, int x, int y, int rgb);
t_dist 		dda(t_data *data, double ray_x, double ray_y);
void		get_player_pos(t_player *player, char **map);
int			frame(t_data *data);
void		new_image(t_data *data);
int			on_key_up(int keypress, t_data *data);
int 		on_key_down(int keypress, t_data *data);
int			ft_strlen(const char *s);
char		*get_next_line(int fd);
int			count_line(char *av);
char		**get_map(int fd, int count);
int			handle_mouse(int x, int y, t_data *data);
int			mlx_mouse_move(void *win_ptr, int x, int y);

# endif