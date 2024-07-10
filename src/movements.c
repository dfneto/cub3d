/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:28:49 by davifern          #+#    #+#             */
/*   Updated: 2024/07/10 11:36:41 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_to_left_original(t_img *img, t_player *player)
{
	int		x;
	int		y;
	
    x = 0;
	y = 0;
	player->x -= player->speed;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
            //apago o que tinha antes pitando de preto
            my_mlx_pixel_put(img, x, y, BLACK);
            
			//make the map borders
			if ((x > 490 || x < 10) || (y > 490 || y < 10))
				my_mlx_pixel_put(img, x, y, YELLOW);
			
            if ((player->x > 10 && player->x < 490) && 
				(x > player->x - player->speed && x < player->x + player->size - player->speed) 
				&&  (y > player->y && (y < player->y + player->size)))
				my_mlx_pixel_put(img, x, y, YELLOW);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(img->win->mlx_ptr,
		img->win->win_ptr, img->img_ptr, 0, 0);
	return (0);
}
