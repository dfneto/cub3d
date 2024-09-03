/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:25 by davifern          #+#    #+#             */
/*   Updated: 2024/09/03 17:11:53 by davifern         ###   ########.fr       */
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
# define TEXWIDTH 	64 //tamanho da textura: uma imagem xpm de 64x64 pxl
# define TEXHEIGHT 	64
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
# define KEYPRESS		2
# define KEYRELEASE		3

# define MINI_WALL_SIZE	8
# define ROT_SPEED		0.09
# define PLAYER_SPEED	0.2
# define PLAYER_SIZE		2

# define EXTENSION ".cub"
# define VALID_CHAR	"01 NEWS"

//img_ptr is a pixel vector that will be plot. 
//It represents the image in the window
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
	int		w;
	int		h;
}		t_img;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
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
}	t_textures;

//x e y sao as coordenadas do jogador no map grid (mapa de 0s e 1s) e sao float
//porque depois serao convertidas em pixels no mapa e 
//assim tenham mais possibilidades de valores do que inteiros
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			size;
	int			map_x;
	int			map_y;
	float		speed;
}	t_player;

// int			player_grid_x; x do player no map
// int			player_grid_y; y do player no map
//player_grid_direction: representa a direcao do player: N, S, W, E
typedef struct s_data
{
	t_img		*img;
	t_player	*player;
	char		**map;
	int			**buffer;
	int			map_w;
	int			map_h;
	t_textures	*textures;
	t_ray		*ray;
	void		*mlx_ptr;
	void		*win_ptr;
	int			*tile;
	char		player_grid_direction;
	int			player_grid_x;
	int			player_grid_y;
	int			number_of_players;
	int			w;
	int			s;
	int			a;
	int			d;
	int			r;
	int			l;
}	t_data;

//inits.c
void	init_window_and_image(t_data *data);
void	init_player(t_data *data);
void	init_ray(t_ray *ray);

//inits_utils.c
void	set_to_north_or_south(t_player *player, double dir);
void	set_to_east_or_west(t_player *player, double dir);

//dda.c
void	execute_dda(t_ray *ray, char **grid_map, int height, int width);
void	set_dda(t_ray *ray, t_player *player);

//rotation.c
void	rotate_left_right(t_player *player, double rot_speed);

//movements.c
int		is_next_position_valid(t_data *data,
			double next_x, double next_y);
void	calculate_position_forward(t_player *player,
			double *next_x, double *next_y);
void	calculate_position_back(t_player *player,
			double *next_x, double *next_y);
void	calculate_position_left(t_player *player,
			double *next_x, double *next_y);
void	calculate_position_right(t_player *player,
			double *next_x, double *next_y);

//raycasting_utils.c
t_img	*define_wall_texture(t_ray *ray, t_textures *textures);
void	calculate_line_height(t_ray *ray);
void	calculate_wall_x(t_ray *ray, t_player *player);
void	calculate_ray_direction_and_delta(t_ray *ray, t_player *player);
void	calculate_wall_distance(t_ray *ray);

//render.c
void	render(t_data *data);
void	draw_with_raycasting(t_data *data);
void	update_player_position(t_player *player, t_data *data);

// render_utils.c
void	render_buffer(int **buffer, t_img *img);
void	clean_buffer(int **buffer);
void	apply_position(t_player *player, double next_x, double next_y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//errors.c
void	clean_exit(t_data *data, char *msg);

// minimap.c
void	draw_minimap(t_data *data);
void	draw_player(t_img *img, t_player *player);
void	draw_map_walls(t_img *img, t_data *data);
void	draw_the_wall(t_img *img, int row, int column, int color);

//color_floor_ceiling.c
void	color_floor(t_data *data, int **buffer, int drawStart, int x);
void	color_ceiling(t_data *data, int **buffer, int drawEnd, int x);

//hooks.c
void	set_hooks(t_data *data);

//set_texture_pixels.c
void	set_wall_texture_pixels(t_ray *ray, int **buffer,
			int x, t_textures *textures);

/* LUKITA START */
// era tua funçao mas adicionei ela aqui
void	invert_grid(t_data *data);

//parse_input.c
void	parse_input(char *argv, t_data *data);

//open_utils.c
int		ft_open(char *filename);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *s1, char *s2, int clean_it);

//read_utils.c
char	**ft_read(int fd);

//parse_texture.c
int		is_textures_ok(t_textures *tex);
void	check_texture_input(char *line, t_data *data);

//image_utils.c
t_img	*new_file_img(char *path, t_data *data);
int		*create_new_color(char *path);

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

#endif