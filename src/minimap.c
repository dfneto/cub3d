/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/08/30 15:26:00 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, t_player *player)
{
	float	x;
	float	y;
	float	x_pixel;
	float	y_pixel;

	//Conversao de linhas/colunas do map grid em pixels
	x_pixel = (player->pos_x) * MINI_WALL_SIZE;
	y_pixel = (player->pos_y) * MINI_WALL_SIZE;
	x = x_pixel - player->size / 2;
	y = y_pixel - player->size / 2;
	while (y >= y_pixel - player->size / 2 && y <= y_pixel + player->size / 2)
	{
		while (x >= x_pixel - player->size / 2 && x <= x_pixel + player->size / 2)
		{
			my_mlx_pixel_put(img, x, y, RED); //TODO: ver como ocorre 
			//a conversão de floats em inteiros
			x++;
		}
		x = x_pixel - player->size / 2;
		y++;
	}
}

//fill WALL_SIZE x WALL_SIZE pixels according to [row, column] of the 
//grid map
void	draw_the_wall(t_img *img, int row, int column, int color)
{
	int	y;
	int	x;
	
	//converto de linhas e colunas para pixels
	row++;
	column++;
	y = row * MINI_WALL_SIZE - MINI_WALL_SIZE; 
	x = column * MINI_WALL_SIZE - MINI_WALL_SIZE;
	
	while (y < row * MINI_WALL_SIZE)
	{		
		while (x < column * MINI_WALL_SIZE)
		{						
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		x = column * MINI_WALL_SIZE - MINI_WALL_SIZE;
		y++;
	}
}

// if it's one fill the pixel with some color else with black
void	draw_map_walls(t_img *img, t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < data->map_h)
	{
		j = 0;
		while (j < data->map_w)
		{
			if (data->map[i][j] == '1')
				draw_the_wall(img, i, j, YELLOW);
			else if (data->map[i][j] == '2')
				draw_the_wall(img, i, j, RED);
			else if (data->map[i][j] == '3')
				draw_the_wall(img, i, j, BLUE);
			else if (data->map[i][j] == '4')
				draw_the_wall(img, i, j, WHITE);
			else
				draw_the_wall(img, i, j, BLACK);
			j++;
		}
		i++;
	}
}
// t_point_distance end_point = 
//dda_collision_detection_lodev(player, img->win->map);
// int	endX = (end_point.x) * WALL_SIZE; //(player->x + 0 + 0.5) 
//* WALL_SIZE; //1.5 é o tamanho da direction line
// int	endY = (end_point.y) * WALL_SIZE; //(player->y - 8) *
// WALL_SIZE; //TODO: pq + 0.5?
//it draws a line
int draw_direction_line(t_img *img, t_player *player, int beginX, int beginY)
{
	int color = BLUE;
	//Conversao de linhas/colunas do map grid em pixels
	beginX = (player->pos_x) * MINI_WALL_SIZE; 
	//0.5 para colocar o jogador no meio do quadrado (WALL_SIZE)
	beginY = (player->pos_y) * MINI_WALL_SIZE;
	
	//1.5 é o tamanho da direction line
	int	endX = (player->pos_x + player->dir_x * 1.5) * MINI_WALL_SIZE; 
	int	endY = (player->pos_y + player->dir_y * 1.5) * MINI_WALL_SIZE;
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

void	draw_minimap(t_data *data)
{
	draw_map_walls(data->img, data);
	draw_player(data->img, data->player);
	draw_direction_line(data->img, data->player,
		data->player->pos_x, data->player->pos_y);
}