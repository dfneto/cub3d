/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/08/08 10:21:14 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	y = HEIGHT - y - 1;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

//N: [0 1], W: [-1 0], S: [0 -1], O: [1  0]
//O vetor posição x e y são colunas e linhas e não coordenadas cartesianas
//cria o player com base nas coordenadas do grid
t_player	create_player(t_map *map)
{
	int i = 0;
	int j = 0;
	t_player    player; //TODO: devo criar um malloc? Pq sim ou pq não?

	while (i < ROWS) //y
	{
		while (j < COLS) //x
		{
			if (map->grid[i][j] == 'N') // [0 1]
			{
				player.x = j + 0.5; //0.5 para que a posicao x seja no centro e nao na esquina
				player.y = row_inverter(i) + 0.5;
				player.dir_x = 0.0;
				player.dir_y = 1.0;
			}
			if (map->grid[j][i] == 'S') // [0 -1]
			{
				player.x = j + 0.5;
				player.y = row_inverter(i) + 0.5;
				player.dir_x = 0.0;
				player.dir_y = -1.0;
			}
			j++;
		}
		j = 0;
		i++;
	}
	// player.planeX = 0;
    // player.planeY = -0.66;
	player.size = 20;
    player.direction_line_size = 200;
	return player;
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