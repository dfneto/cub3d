/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:25 by davifern          #+#    #+#             */
/*   Updated: 2024/07/11 11:15:52 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h> 
# include <stdlib.h>
# include "messages.h"

# define WIDTH		500
# define HEIGHT		500
# define THICKNESS	10
# define ESC		65307 //53
# define LEFT_CLICK 1
# define KEY_A		97 //0
# define KEY_D		100 //2
# define KEY_W		119 //13
# define KEY_S		115 //1
# define KEY_C		8


typedef struct s_win
{
	int				height;
	int				width;
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	*img;
	struct s_player	*player;
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

typedef struct s_player
{
	int		x;
	int		y;
	int		size;
	int		speed;
	float		dir_x;
	float		dir_y;
	int		direction_line_size;
}	t_player;

// cub3d.c
void	draw_game_board(t_img *img, t_player *player);

//utils.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//hooks.c
void	set_hooks(t_win *window);

//movements
int		move_to_left(t_img *img, t_player *player);


#endif
