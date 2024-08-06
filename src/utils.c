/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/08/06 16:54:55 by davifern         ###   ########.fr       */
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
				player->x = j + 0.5; //0.5 para que a posicao x seja no centro e nao na esquina
				player->y = i + 0.5;
				player->dir_x = 0.0;
				player->dir_y = 1.0;
			}
			if (map->grid[i][j] == 'S') // [0 -1]
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				player->dir_x = 0.0;
				player->dir_y = -1.0;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

// fill all the pixels with black
void	clean_map(t_img *img)
{
	int i = 0;
	int j = 0;
	
	while (i < ROWS)
	{
		while (j < COLS)
		{
			// draw_the_wall(img, j + 1, i + 1, BLACK);
			my_mlx_pixel_put(img, j, i, BLACK);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(img->win->mlx_ptr,
		img->win->win_ptr, img->win->img->img_ptr, 0, 0);
}