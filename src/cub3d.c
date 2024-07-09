/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/09 10:18:17 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_game_board(t_img *img, t_player *player)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			//make the map borders
			if ((x > 490 || x < 10) || (y > 490 || y < 10))
				my_mlx_pixel_put(img, x, y, YELLOW);
			
			//make the player 10x10 pxl
			if ((x > player->x && (x < player->x + player->size))
					&& (y > player->y && (y < player->y + player->size)))
				my_mlx_pixel_put(img, x, y, RED);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(img->win->mlx_ptr,
		img->win->win_ptr, img->img_ptr, 0, 0);
}