/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 12:40:22 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	color_floor(t_data *data, int **buffer, int drawStart, int x)
{
	int	y;

	y = 0;
	while (y < drawStart)
	{
		buffer[y][x] = *data->textures->floor;
		y++;
	}
}

void	color_ceiling(t_data *data, int **buffer, int drawEnd, int x)
{
	int	y;

	y = drawEnd;
	while (y < HEIGHT)
	{
		buffer[y][x] = *data->textures->ceiling;
		y++;
	}
}
