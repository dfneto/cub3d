/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:43:59 by davifern          #+#    #+#             */
/*   Updated: 2024/08/21 19:55:44 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	y = HEIGHT - y - 1; //mac
	// y = HEIGHT - y; //linux
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	// int	pixel;

	// pixel = y * (img->line_len / 4) + x;
	// img->addr[pixel] = color;
}

//N: [0 1], W: [-1 0], S: [0 -1], O: [1  0]
//O vetor posição x e y são colunas e linhas e não coordenadas cartesianas
//cria o player com base nas coordenadas do grid
//TODO: colocar um break no inner while e um flag de player_set para nao ficar no loop mesmo depois de ter setado o jogador
t_player	create_player(t_map *map)
{
	int y = 0;
	int x = 0;
	
	t_player    player; //TODO: devo criar um malloc? Pq sim ou pq não?

	while (y < ROWS) //y < 5
	{
		while (x < COLS) //x < 6
		{
			if (map->grid[y][x] == 'N') // [0 1]
			{
				player.pos_x = x + 0.5; //0.5 para que a posicao x seja no centro e nao na esquina
				player.pos_y = y + 0.5;
				player.dir_x = 0.0;
				player.dir_y = 1.0;
				player.planeX = 0.66;
				player.planeY = 0.0;
			}
			if (map->grid[y][x] == 'S') // [0 -1]
			{
				player.pos_x = x + 0.5;
				player.pos_y = y + 0.5;
				player.dir_x = 0.0;
				player.dir_y = -1.0;
				player.planeX = -0.66;
				player.planeY = 0;
			}		
			x++;
		}
		x = 0;
		y++;
	}
	player.size = PLAYER_SIZE;
	return player;
}