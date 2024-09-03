/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:48:55 by davifern          #+#    #+#             */
/*   Updated: 2024/09/03 16:55:49 by davifern         ###   ########.fr       */
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

//Em algum momento isso foi válido
// y = HEIGHT - y - 1; //mac
// y = HEIGHT - y; //linux
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	y = HEIGHT - y - 1;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	// int	pixel;s

	// pixel = y * (img->line_len / 4) + x;
	// img->addr[pixel] = color;
}