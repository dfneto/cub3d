/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:55 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 11:51:21 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_buffer(int **buffer, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(img, x, y, buffer[y][x]);
			x++;
		}
		y++;
	}
}

void	clean_buffer(int **buffer)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			buffer[y][x++] = 0;
		y++;
	}
}

//Apply the next position to the player
void	apply_position(t_player *player, double next_x, double next_y)
{
	player->pos_x = next_x;
	player->pos_y = next_y;
}
