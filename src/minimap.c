/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/09/06 18:25:08 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Conversao de linhas/colunas do map grid em pixels:
//quando multiplico uma posição por MINI_WALL_SIZE:
// x_pixel = (player->pos_x) * MINI_WALL_SIZE;
//Entender como ocorre a conversão de floats em inteiros:
// my_mlx_pixel_put(img, x, y, RED); 
void	draw_player(t_img *img, t_player *player)
{
	float	x;
	float	y;
	float	x_pixel;
	float	y_pixel;

	x_pixel = (player->pos_x) * MINI_WALL_SIZE;
	y_pixel = (player->pos_y) * MINI_WALL_SIZE;
	x = x_pixel - player->size / 2;
	y = y_pixel - player->size / 2;
	while (y >= y_pixel - player->size / 2 && y <= y_pixel + player->size / 2)
	{
		while (x >= x_pixel - player->size / 2 && x <= x_pixel
			+ player->size / 2)
		{
			my_mlx_pixel_put(img, x, y, RED);
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

//it draws a line
//1.5 é o tamanho da direction line
int	draw_direction_line(t_img *img, t_player *player,
		double begin_x, double begin_y)
{
	double	delta_x;
	double	delta_y;
	int		end_x;
	int		end_y;
	int		pixels;

	begin_x = (player->pos_x) * MINI_WALL_SIZE;
	begin_y = (player->pos_y) * MINI_WALL_SIZE;
	end_x = (player->pos_x + player->dir_x * 1.5) * MINI_WALL_SIZE;
	end_y = (player->pos_y + player->dir_y * 1.5) * MINI_WALL_SIZE;
	delta_x = end_x - begin_x;
	delta_y = end_y - begin_y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x = delta_x / pixels;
	delta_y = delta_y / pixels;
	while (pixels)
	{
		my_mlx_pixel_put(img, begin_x, begin_y, BLUE);
		begin_x += delta_x;
		begin_y += delta_y;
		pixels--;
	}
	return (0);
}

void	draw_minimap(t_data *data)
{
	draw_map_walls(data->img, data);
	draw_player(data->img, data->player);
	draw_direction_line(data->img, data->player,
		data->player->pos_x, data->player->pos_y);
}
