/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/09/03 16:58:23 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
