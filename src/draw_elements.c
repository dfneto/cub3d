/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/22 12:17:46 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, t_player *player)
{
	int	x;
	int	y;

	x = player->x - player->size/2;
	y = player->y - player->size/2;
	while (y >= player->y - player->size/2 && y <= player->y + player->size/2)
	{
		while (x >= player->x - player->size/2 && x <= player->x + player->size/2)
			my_mlx_pixel_put(img, x++, y, RED);
		x = player->x - player->size/2;
		y++;
	}
}

/*
Before to draw the borders paint everything with black pixels. 
It's a way to clean the window every time you are going to 
print the boarders and so not to use the mlx_clear_window 
(Clears the current window. This is not a recommended function 
to use. Instead it is recommended to use the function 
mlx_put_image_to_window with a recycled image that you 
have cleared).
*/
void	draw_borders(t_img *img)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
            my_mlx_pixel_put(img, x, y, BLACK);
			if ((x > WIDTH - THICKNESS || x < THICKNESS) 
				|| (y > HEIGHT - THICKNESS || y < THICKNESS))
				my_mlx_pixel_put(img, x, y, YELLOW);
			x++;
		}
		x = 0;
		y++;
	}
}

void	fill_black(t_img *img, int counter)
{
	int wall_size = 64;
	int x = counter * wall_size - wall_size;
	int y = counter * wall_size - wall_size;
	while (x < counter * wall_size)
	{
		while (y < counter * wall_size)
		{
			my_mlx_pixel_put(img, x, y, BLACK);
			y++;
		}
		y = counter * wall_size - wall_size;
		x++;
	}

}

//TODO: se o player passar da parede superior da seg fault
void	draw_the_wall(t_img *img, int x_counter, int y_counter, int color)
{
	int	x;
	int	y;
	
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

void	draw_map_grid(t_img *img, t_map *map)
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

// Desenho una linha fixa saindo do player->y (meio) para cima
void	draw_player_direction_inicial(t_img *img, t_player *player)
{
	int	y;
	y = player->y - player->direction_line_size;
	while (y >= player->y - player->direction_line_size 
		&& y <= player->y)
	{
		my_mlx_pixel_put(img, player->x, y, BLUE);
		y++;
	}
}

//Usar a função bresenham abaixo?
int draw_direction_line(t_img *img, t_player *player, int beginX, int beginY, int color)
{
	int	endX = beginX + player->delta_x*50;
	int	endY = beginY - player->delta_y*50;
	double deltaX = endX - beginX; 
	double deltaY = endY - beginY; 
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX = deltaX / pixels; 
	deltaY = deltaY / pixels; 
	double pixelX = beginX;
	double pixelY = beginY;
	my_mlx_pixel_put(img, 300, 300, 0xFF0000);
	while (pixels)
	{
		printf("pixelX=%f, pixelY=%f\n", pixelX, pixelY);
		// mlx_pixel_put(mlx, win, pixelX, pixelY, 0xFFFFFF);
		my_mlx_pixel_put(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return 0;
}
/*
#define MAXI(a, b) (a> b?a: b)
#define MOD(a) ((a < 0) ? -a: a)
void bresenham(float x, float y, float x1, float y1, fdf *data)//(1:1) (3:12)
{
    float x_step;
    float y_step;
    int max;

    x_step = x1
    y_step = y1

    max = MAX(MOD (x_step), MOD(y_step)):
    x_step /= max;
    y_step /= max;

    while ((int) (x - x1) || (int) (y- y1))
    {
        mix pixel put(data-›mlx ptr, data-›win ptr, x, y, oxffffff):
        x += x_step;
        y += y_step;
    }
}
*/

void	draw_player_direction(t_win *win, t_player *player)
{
 	draw_direction_line(win->img, player, player->x, player->y, BLUE);
}

void	draw_game_board(t_win *win)
{
//	draw_borders(win->img);
	draw_map_grid(win->img, win->map);
	draw_player(win->img, win->player);
// mlx_pixel_put(win->mlx_ptr, win->win_ptr, 312, 312, 0xFF0000); por que não funciona???
	draw_player_direction(win, win->player);
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
}
