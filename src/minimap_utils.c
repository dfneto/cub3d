/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/09/03 20:26:40 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_the_line(int pixels, int pixel_x, int pixel_y, int color)
{
	while (pixels)
	{
		my_mlx_pixel_put(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}
