/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/08 11:02:56 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	plot_game_board(t_img *img)
{
	int		x;
	int		y;
	t_win	*win;

	x = 0;
	y = 0;
	win = img->win;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			//make the map borders
			if ((x > 490 || x < 10) || (y > 490 || y < 10))
				my_mlx_pixel_put(img, x, y, YELLOW);
			
			//make the player 10x10 pxl
			if ((x > 64 && x < 74) && (y > 340 && y < 350))
				my_mlx_pixel_put(img, x, y, RED);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, img->img_ptr, 0, 0);
}