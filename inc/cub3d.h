/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:03:25 by davifern          #+#    #+#             */
/*   Updated: 2024/07/08 13:29:56 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h> 
# include <stdlib.h>
# include "messages.h"

# define WIDTH 500
# define HEIGHT 500
# define ESC 53
# define LEFT_CLICK 1

typedef struct s_win
{
	int				height;
	int				width;
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	*img;
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

// cub3d.c
void	plot_game_board(t_img *img);

//utils.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//hooks.c
void	set_hooks(t_win *window);


#endif