/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/29 06:36:54 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, t_player *player)
{
	float	x;
	float	y;
	float x_pixel;
	float y_pixel;

	//Conversao de linhas/colunas do map grid em pixels
	x_pixel = (player->x + 0.5) * WALL_SIZE;
	y_pixel = (player->y + 0.5) * WALL_SIZE;
	
	x = x_pixel - player->size/2;
	y = y_pixel - player->size/2;
	while (y >= y_pixel - player->size/2 && y <= y_pixel + player->size/2)
	{
		while (x >= x_pixel - player->size/2 && x <= x_pixel + player->size/2)
			my_mlx_pixel_put(img, x++, y, RED); //TODO: ver como ocorre a conversão de floats em inteiros
		x = x_pixel - player->size/2;
		y++;
	}
}

void	draw_the_wall(t_img *img, int x_counter, int y_counter, int color)
{
	int	x;
	int	y;
	
	//converto de linhas e colunas para pixels
	x = x_counter * WALL_SIZE - WALL_SIZE; 
	y = y_counter * WALL_SIZE - WALL_SIZE;
	
	while (y < y_counter * WALL_SIZE)
	{		
		while (x < x_counter * WALL_SIZE)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		x = x_counter * WALL_SIZE - WALL_SIZE;
		y++;
	}
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
				draw_the_wall(img, j + 1, i + 1, YELLOW);
			else
				draw_the_wall(img, j + 1, i + 1, BLACK);
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
	beginX = (player->x + 0.5) * WALL_SIZE; //0.5 para colocar o jogador no meio do quadrado (WALL_SIZE)
	beginY = (player->y + 0.5) * WALL_SIZE;
	int	endX = (player->x + player->dir_x * 1.5 + 0.5) * WALL_SIZE; //1.5 é o tamanho da direction line
	int	endY = (player->y - player->dir_y * 1.5 + 0.5) * WALL_SIZE;
	
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

void	draw_game_board(t_win *win)
{
	draw_map_walls(win->img, win->map);
	draw_grid_lines(win);
	draw_player(win->img, win->player);
	draw_player_direction_line(win->img, win->player, win->player->x, win->player->y, BLUE);
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
	// mlx_pixel_put(win->mlx_ptr, win->win_ptr, 312, 312, 0xFF0000); por que não funciona???
}
