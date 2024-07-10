/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/10 11:30:03 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, t_player *player)
{
	int	x;
	int	y;

	x = player->x - player->size/2;
	y = player->y - player->size/2;
	while (y >= player->y - player->size/2 && y <= player->y + player->size/2)
	{
		while (x >= player->x - player->size/2 && x <= player->x + player->size/2)
			my_mlx_pixel_put(img, x++, y, RED);
		x = player->x - player->size/2;
		y++;
	}
}

/*
Before to draw the borders paint everything with black pixels. 
It's a way to clean the window every time you are going to 
print the boarders and so not to use the mlx_clear_window 
(Clears the current window. This is not a recommended function 
to use. Instead it is recommended to use the function 
mlx_put_image_to_window with a recycled image that you 
have cleared).
*/
void	draw_borders(t_img *img)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
            my_mlx_pixel_put(img, x, y, BLACK);
			if ((x > WIDTH - THICKNESS || x < THICKNESS) 
				|| (y > HEIGHT - THICKNESS || y < THICKNESS))
				my_mlx_pixel_put(img, x, y, YELLOW);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_game_board(t_img *img, t_player *player)
{
	mlx_clear_window(img->win->mlx_ptr, img->win->win_ptr);
	draw_borders(img);
	draw_player(img, player);
	mlx_put_image_to_window(img->win->mlx_ptr,
		img->win->win_ptr, img->img_ptr, 0, 0);
}