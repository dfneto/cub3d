/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/07/26 11:55:30 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

//N: [0 1], W: [-1 0], S: [0 -1], O: [1  0]
//O vetor posição x e y são colunas e linhas e não coordenadas cartesianas
void	set_player_position_and_direction(t_player *player, t_map *map)
{
	int i = 0;
	int j = 0;
	
	while (i < ROWS) //y
	{
		while (j < COLS) //x
		{
			if (map->grid[i][j] == 'N') // [0 1]
			{
				player->x = j;
				player->y = i;
				player->dir_x = 0.0;
				player->dir_y = 1.0;
				printf("set player x=%f, y=%f\n", player->x, player->y);
			}
			if (map->grid[i][j] == 'S') // [0 -1]
			{
				player->x = j;
				player->y = i;
				player->dir_x = 0.0;
				player->dir_y = -1.0;
				printf("set player x=%f, y=%f\n", player->x, player->y);
			}
			j++;
		}
		j = 0;
		i++;
	}
}