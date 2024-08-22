/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:25 by davifern          #+#    #+#             */
/*   Updated: 2024/08/22 16:12:02 by davifern         ###   ########.fr       */
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
# define texWidth 	64 //tamanho da textura: uma imagem xpm de tamanho 64x64 pixels
# define texHeight 	64
# define ESC		53 //65307 //53
# define LEFT_CLICK 1
# define KEY_A		0 //97 //0
# define KEY_D		2 //100 //2
# define KEY_W		13 //119 //13
# define KEY_S		1 //115 //1
# define KEY_C		8
# define KEY_LEFT	123 //65361 //123
# define KEY_RIGTH	124 //65363 //124

#define ROWS 			24
#define COLS 			24
#define MINI_WALL_SIZE	8
#define ROT_SPEED		0.09
#define PLAYER_SPEED	0.2
#define PLAYER_SIZE		2

//img_ptr is a pixel vector that will be plot. 
//It represents the image in the window
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;

typedef struct s_ray
{
    int		hit;
    int		mapX;
    int		mapY;
    int		stepX;
    int		stepY;
    int		side;
    int		lineHeight;
	double	rayDirX;
    double	rayDirY;
    double	cameraX;
    double	deltaDistX;
    double	deltaDistY;
    double	sideDistX;
    double	sideDistY;
    double	wall_distance;
}	t_ray;

typedef struct s_texture
{
	void		*img_ptr;
	char 		*addr;
	int			bpp;
	int			endian;
	int			line_len;
}	t_texture;


//x e y sao as coordenadas do jogador no map grid (mapa de 0s e 1s) e sao float
//porque depois serao convertidas em pixels no mapa e assim tenham mais possibilidades
//de valores do que inteiros
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		planeX;
    double		planeY;
	int			size;
	int			map_x;
	int 		map_y;
	float		speed;
}	t_player;

typedef struct s_point_distance
{
	float		x;
	float		y;
	float		distance;
}	t_point_distance;

typedef struct s_map
{
	char	grid[ROWS][COLS]; //ROWS=y, COLS=x
}	t_map;

typedef struct s_data
{
	t_img		*img;
	t_player	*player;
	t_map		*map;
	t_ray		*ray;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_data;

//inits.c
void    init_window_and_image(t_data *data);
void    init_map(t_data *data);
void	init_player(t_data *data);
void    init_ray(t_ray *ray);

//render.c
void    render(t_data *data);

//errors.c
void clean_exit(t_data *data, char *msg);

// draw_elements.c
void	draw_minimap(t_data *data);
void	draw_player(t_img *img, t_player *player);
void	draw_map_walls(t_img *img, t_map *map);
void	draw_the_wall(t_img *img, int row, int column, int color);
int	is_player_inside_the_borders_map(t_player *player);
int draw_player_direction_line(t_img *img, t_player *player, int beginX, int beginY, int color);

//utils.c
void	clean_map(t_img *img);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_player	create_player(t_map *map);

//hooks.c
void	set_hooks(t_data *data);

//bresenham
void	draw_grid_lines(t_data *data);

//dda
t_point_distance	dda_collision_detection_lodev(t_player *player, t_map *map);
int	has_wall(t_player *player);

//draw_everything_3d.c
void	draw_everything_3d(t_data *data);
void draw_everything_3d_texture(t_data *data);

void calculate_wall_distance(t_ray *ray);

void calculate_wall_distance(t_ray *ray);

void calculate_ray_direction_and_delta(t_ray *ray, t_player *player);

void calculate_side_dist_wall_position_and_side(t_ray *ray, t_map *grid_map);
void calculate_side_dist_and_step(t_ray *ray, t_player *player);

// utils2.c
void print_map_grid(t_map *map);
int get_rgb(int r, int g, int b);

#endif