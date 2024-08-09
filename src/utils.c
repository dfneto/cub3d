/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/08/09 13:34:40 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	// y = HEIGHT - y - 1; //mac
	y = HEIGHT - y; //linux
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

//N: [0 1], W: [-1 0], S: [0 -1], O: [1  0]
//O vetor posição x e y são colunas e linhas e não coordenadas cartesianas
//cria o player com base nas coordenadas do grid
//TODO: colocar um break no inner while e um flag de player_set para nao ficar no loop mesmo depois de ter setado o jogador
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
				player.pos_x = j + 0.5; //0.5 para que a posicao x seja no centro e nao na esquina
				player.pos_y = row_inverter(i) + 0.5;
				player.dir_x = 0.0;
				player.dir_y = 1.0;
				player.planeX = 0.66;
				player.planeY = 0.0;
			}
			if (map->grid[j][i] == 'S') // [0 -1]
			{
				player.pos_x = j + 0.5;
				player.pos_y = row_inverter(i) + 0.5;
				player.dir_x = 0.0;
				player.dir_y = -1.0;
				player.planeX = -0.66;
				player.planeY = 0;
			}		
			j++;
		}
		j = 0;
		i++;
	}
	player.size = 20;
    player.direction_line_size = 200;
	return player;
}

// fill all the pixels with black
void	clean_map(t_img *img)
{
	int i;
	int j;
	
	i = 0;
	while (i < ROWS * WALL_SIZE)
	{
		j = 0;
		while (j < COLS * WALL_SIZE)
		{
			// draw_the_wall(img, j + 1, i + 1, BLACK);
			my_mlx_pixel_put(img, row_inverter(i), j, BLACK);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->win->mlx_ptr,
		img->win->win_ptr, img->win->img->img_ptr, 0, 0);
}