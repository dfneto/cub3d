/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:25 by davifern          #+#    #+#             */
/*   Updated: 2024/07/30 13:10:17 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h> 
# include <stdlib.h>
# include "messages.h"

# define WIDTH		768
# define HEIGHT		768
# define THICKNESS	10
# define ESC		65307 //53
# define LEFT_CLICK 1
# define KEY_A		97 //0
# define KEY_D		100 //2
# define KEY_W		119 //13
# define KEY_S		115 //1
# define KEY_C		8
# define KEY_LEFT	65361
# define KEY_RIGTH	65363


#define ROWS 			24
#define COLS 			24
#define WALL_SIZE		32
#define ROT_SPEED		0.09
#define PLAYER_SPEED	0.5


typedef struct s_win
{
	int				height;
	int				width;
	int				zoom;
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	*img;
	struct s_player	*player;
	struct s_map	*map;
}		t_win;

typedef struct s_img
{
	t_win	*win;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;

//x e y sao as coordenadas do jogador no map grid (mapa de 0s e 1s) e sao float
//porque depois serao convertidas em pixels no mapa e assim tenham mais possibilidades
//de valores do que inteiros
typedef struct s_player
{
	float		x;
	float		y;
	t_win		*win;
	int			size;
	float		speed;
	float		dir_x;
	float		dir_y;
	int			direction_line_size;
}	t_player;

typedef struct s_point_distance
{
	float		x;
	float		y;
	float		distance;
}	t_point_distance;

typedef struct s_map
{
	char	grid[ROWS][COLS];
}	t_map;

// draw_elements.c
void	draw_everything(t_win *win);
int	is_player_inside_the_borders_map(t_player *player);
//void	draw_game_board(t_img *img, t_player *player);

//utils.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	set_player_position_and_direction(t_player *player, t_map *map);

//hooks.c
void	set_hooks(t_win *window);

//bresenham
void	draw_grid_lines(t_win *win);

//dda
t_point_distance	dda_collision_detection_lodev(t_player *player, t_map *map);
int	has_wall(t_player *player);

#endif