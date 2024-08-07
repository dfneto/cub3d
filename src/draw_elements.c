/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/08/07 19:48:09 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_inside_the_borders_map(t_player *player)
{
	if (player->x >= 1 && player->x <= 23 && player->y >= 1 && player->y <= 23)
		return 1;
	return 0;

}

void	draw_player(t_img *img, t_player *player)
{
	float	x;
	float	y;
	float x_pixel;
	float y_pixel;

	//Conversao de linhas/colunas do map grid em pixels
	x_pixel = (player->x) * WALL_SIZE;
	y_pixel = (player->y) * WALL_SIZE;
	
	x = x_pixel - player->size/2;
	y = y_pixel - player->size/2;
	while (y >= y_pixel - player->size/2 && y <= y_pixel + player->size/2)
	{
		while (x >= x_pixel - player->size/2 && x <= x_pixel + player->size/2)
		{
			my_mlx_pixel_put(img, x, y, RED); //TODO: ver como ocorre a conversão de floats em inteiros
			x++;

		}
		x = x_pixel - player->size/2;
		y++;
	}
}

//fill WALL_SIZE x WALL_SIZE pixels according to [row, column] of the grid map
void	draw_the_wall(t_img *img, int row, int column, int color)
{
	int	i;
	int	j;
	
	//converto de linhas e colunas para pixels
	row++;
	column++;
	i = row * WALL_SIZE - WALL_SIZE; 
	j = column * WALL_SIZE - WALL_SIZE;
	
	while (i < row * WALL_SIZE) // x < 32
	{		
		while (j < column * WALL_SIZE) // y < 32
		{						//x  y
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		j = column * WALL_SIZE - WALL_SIZE;
		i++;
	}
}

int	row_inverter(int i)
{
	return ROWS - i - 1;
}

// if it's one fill the pixel with some color else with black
void	draw_map_walls(t_img *img, t_map *map)
{
	int i = 0;
	int j = 0;
	
	while (i < ROWS)
	{
		while (j < COLS)
		{
			if (map->grid[i][j] == '1')
				draw_the_wall(img, row_inverter(i), j, YELLOW);
			else if (map->grid[i][j] == 'P')
			{
				printf("Posicao real [row,col] = %d,%d\n", i, j);
				printf("Posicao desejada [row,col] = %d,%d\n", row_inverter(i), j);
				draw_the_wall(img, row_inverter(i), j, BLUE);
			}
			else
				draw_the_wall(img, row_inverter(i), j, BLACK);
			j++;
		}
		j = 0;
		i++;
	}
}
//it draws a line
int draw_player_direction_line(t_img *img, t_player *player, int beginX, int beginY, int color)
{
	//Conversao de linhas/colunas do map grid em pixels
	beginX = (player->x) * WALL_SIZE; //0.5 para colocar o jogador no meio do quadrado (WALL_SIZE)
	beginY = (player->y) * WALL_SIZE;
	
	int	endX = (player->x + player->dir_x * 3) * WALL_SIZE; //1.5 é o tamanho da direction line
	int	endY = (player->y + player->dir_y * 3) * WALL_SIZE; //TODO: pq + 0.5?

	// t_point_distance end_point = dda_collision_detection_lodev(player, img->win->map);
	// int	endX = (end_point.x) * WALL_SIZE; //(player->x + 0 + 0.5) * WALL_SIZE; //1.5 é o tamanho da direction line
	// int	endY = (end_point.y) * WALL_SIZE; //(player->y - 8) * WALL_SIZE; //TODO: pq + 0.5?

	double deltaX = endX - beginX; 
	double deltaY = endY - beginY; 
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX = deltaX / pixels; 
	deltaY = deltaY / pixels; 
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
	return 0;
}

void	draw_everything_2d(t_win *win)
{
	draw_map_walls(win->img, win->map);
	draw_grid_lines(win);
	// if (is_player_inside_the_borders_map(win->player)) //so posso desenhar o jogador se estiver dentro do mapa. Idealmente tbm so poderia mover dentro das paredes (TODO: o jogador deve encontrar parede atras e aos lados)
	// {
		draw_player(win->img, win->player);
		draw_player_direction_line(win->img, win->player, win->player->x, win->player->y, BLUE);
	// }
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
}
