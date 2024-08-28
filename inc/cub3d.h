/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:25 by davifern          #+#    #+#             */
/*   Updated: 2024/08/28 15:32:31 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h> 
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <unistd.h>
# include "messages.h"

# define WIDTH		768
# define HEIGHT		768
# define texWidth 	64 //tamanho da textura: uma imagem xpm de tamanho 64x64 pixels
# define texHeight 	64
# define ESC_M		53 //65307 //53
# define ESC_L		65307
# define LEFT_CLICK 1
# define KEY_A_M	0 //97 //0
# define KEY_A_L	97
# define KEY_D_M	2 //100 //2
# define KEY_D_L	100
# define KEY_W_M	13 //119 //13
# define KEY_W_L	119
# define KEY_S_M	1 //115 //1
# define KEY_S_L	115
# define KEY_C		8
# define KEY_LEFT_M	123 //65361 //123
# define KEY_LEFT_L	65361
# define KEY_RIGHT_M	124 //65363 //124
# define KEY_RIGHT_L	65363

#define MINI_WALL_SIZE	8
#define ROT_SPEED		0.09
#define PLAYER_SPEED	0.2
#define PLAYER_SIZE		2

#define EXTENSION ".cub"
#define VALID_CHAR	"01 NEWS"

//img_ptr is a pixel vector that will be plot. 
//It represents the image in the window
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
	int		w; //adicionei para saber o tamanho da textura
	int		h; //adicionei para saber o tamanho da textura
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
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	int		*floor;
	int		*ceiling;
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

typedef struct s_data
{
	t_img		*img;
	t_player	*player;
	char		**map; //deletei o t_map e substitui por o char**
	int			map_w; //adicionei para saber o tamanho do mapa
	int			map_h; //adicionei para saber o tamanho do mapa
	t_texture	*textures;
	t_ray		*ray;
	void		*mlx_ptr;
	void		*win_ptr;
	int			*tile; //adicionei para saber o tamanho do tile (textura)
	int			player_grid_direction; //transformar em char. representa a direcao do player: N, S, W, E. Mudar o nome para player_grid_direction
	int			player_grid_x; //x do player no map
	int			player_grid_y; //y do player no map
	int			number_of_players; //a quantidade de jogadores no mapa (se mais ou menos de 1 erro)
}	t_data;

//inits.c
void    init_window_and_image(t_data *data);
//void    init_map(t_data *data);
void	init_player(t_data *data);
void    init_ray(t_ray *ray);
//void    init_texture(t_data *data);



/* LUKITA START */

// era tua funçao mas adicionei ela aqui
void    invert_grid(t_data *data);



//parse_input.c
void	parse_input(char *argv, t_data *data);

//open_utils.c
int	ft_open(char *filename);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *s1, char *s2, int clean_it);

//read_utils.c
char	**ft_read(int fd);

//parse_texture.c
int	is_textures_ok(t_texture *tex);
void	check_texture_input(char *line, t_data *data);

//image_utils.c
t_img	*new_file_img(char *path, t_data *data);
int	*create_new_color(char *path);

//safe_allocation.c && safe_allocation2.c
void	*safe_malloc(size_t len);
char	*safe_itoa(int n);
char	*safe_strdup(const char *s1);
void	*safe_calloc(size_t count, size_t size);
char	**safe_split(char const *s, char c);
char	*safe_strjoin(char const *s1, char const *s2);
char	*safe_strtrim(char const *s1, char const *set);
char	*safe_substr(char const *s, unsigned int start, size_t len);
void	*ft_free(void *ptr);

//ft_strtok.c
char	*ft_strtok(char *input, const char *delim);

//ft_perror.c
void	ft_perror(int err, char *msg);

//check_map.c
void	create_square_map(char **tmp, t_data *data);
void	get_map_size(t_data *data);
void	check_valid_char(t_data *data);

//clean_utils.c
void	clean_array(void *array);

//check_closed.c
void	check_closed(t_data *data);

//invert_image.c
void	invert_image_x(t_img *img);

//fake_split.c
char	**fake_split(char const *s, char c);



/* LUKITA ENDS */



//render.c
void    render(t_data *data);

//textures.c
t_img *loadTexture(void *mlx, char *file_path, int *width, int *height);
void    color_floor(t_data *data, unsigned int buffer[HEIGHT][WIDTH], int drawStart, int x);
void    color_ceiling(t_data *data, unsigned int buffer[HEIGHT][WIDTH], int drawEnd, int x);

//errors.c
void clean_exit(t_data *data, char *msg);

// draw_elements.c
void	draw_minimap(t_data *data);
void	draw_player(t_img *img, t_player *player);
void	draw_map_walls(t_img *img, t_data *data);
void	draw_the_wall(t_img *img, int row, int column, int color);
int	is_player_inside_the_borders_map(t_player *player);
int draw_player_direction_line(t_img *img, t_player *player, int beginX, int beginY, int color);

//utils.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
//t_player	create_player(t_map *map);


//hooks.c
void	set_hooks(t_data *data);

//bresenham
void	draw_grid_lines(t_data *data);

//dda
t_point_distance	dda_collision_detection_lodev(t_player *player, t_data *data);
int	has_wall(t_player *player);

//draw_everything_3d.c
void	draw_everything_3d(t_data *data);
void draw_everything_3d_texture(t_data *data);

void calculate_wall_distance(t_ray *ray);

void calculate_wall_distance(t_ray *ray);

void calculate_ray_direction_and_delta(t_ray *ray, t_player *player);

void calculate_side_dist_wall_position_and_side(t_ray *ray, char **grid_map);
void calculate_side_dist_and_step(t_ray *ray, t_player *player);

// utils2.c
void print_map_grid(t_data *data);
int get_rgb(int r, int g, int b);

#endif