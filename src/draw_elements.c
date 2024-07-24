/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/24 10:07:21 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MAX(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)

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
			my_mlx_pixel_put(img, x++, y, RED);
		x = x_pixel - player->size/2;
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

// for every wall on the map grid draw it
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


//x, y, x1, y1: são as linhas e colunas (coordenadas os 0s e 1s) do grid map, mas não são os 0s e 1s.
	// draw_line_bresenham(700, 400, 500,500, win); - da ruim
	// draw_line_bresenham(400, 700, 500,500, win); - da ruim
void	draw_line_bresenham(int x, int y, int x1, int y1, t_win *win)//(1:1) (3:12)
{
    float x_step;
    float y_step;
    int max;

    x_step = x1 - x;
    y_step = y1 - y;

    max = MAX(MOD(x_step), MOD(y_step));
    x_step /= max;
    y_step /= max;

    while ((int) (x - x1) || (int) (y - y1))
    {
		printf("x=%d, y=%d\n", x, y);
        // mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, YELLOW);
		my_mlx_pixel_put(win->img, x, y, BLUE);
        x += x_step;
        y += y_step;
    }
}

//TODO: por que float?
//x, y, x1, y1: são as linhas e colunas (coordenadas os 0s e 1s) do grid map, mas não são os 0s e 1s.
void draw_grid_bresenham(float x, float y, float x1, float y1, t_win *win)//(1:1) (3:12)
{
    float x_step;
    float y_step;
    int max;
	int z;

	// ao multiplicar pelo zoom eu saio do mundo de linhas e colunas do grid map (coordenadas do grid map) e vou para o mundo de pixels
	// que serão preenchidos no while abaixo step por step (step=1)
	x *= win->zoom;
	y *= win->zoom;
	x1 *= win->zoom;
	y1 *= win->zoom;
    
	z = win->map->grid[(int) y][(int) x];
	int color = (z) ? RED : 0xffffff;
	x_step = x1 - x;
    y_step = y1 - y;

    max = MAX(MOD(x_step), MOD(y_step));
    x_step /= max;
    y_step /= max;

	//para cada linha na horizontal e vertical, vai pixel por pixel
    while ((int) (x - x1) || (int) (y - y1))
    {
		printf("x-x1=%d, y-y1=%d\n", (int) (x - x1), (int) (y - y1));
        // mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, YELLOW);
		my_mlx_pixel_put(win->img, x, y, color);
        x += x_step;
        y += y_step;
    }
}

void	draw_grid_lines(t_win *win)
{
	(void) win;
	int	x;
	int	y;

	y = 0;
	while (y < win->height)
	// while (y < 4)
	{
		x = 0;
		while (x < win->width)
		// while (x < 4)
		{
			// if (x < win->width)
				draw_grid_bresenham(x, y, x + 1, y, win);//[0 0] [1 0]
			// if (y < win->height)
				draw_grid_bresenham(x, y, x, y + 1, win); //[0 0] [0 1]
			x++;
		}
		y++;
	}
}

//Usar a função bresenham abaixo?
int draw_player_direction_line(t_img *img, t_player *player, int beginX, int beginY, int color)
{
	beginX = (player->x + 0.5) * WALL_SIZE;// converter en pixel usando regla de 3
	beginY = (player->y + 0.5) * WALL_SIZE;// converter en pixel
	int	endX = (player->x + player->dir_x * 1.5 + 0.5) * WALL_SIZE; // e converto para pixel
	int	endY = (player->y - player->dir_y * 1.5 + 0.5) * WALL_SIZE;// converto para pixel
	printf("endX=%d, endY=%d\n", endX, endY);
	// int	endX = beginX + player->direction_line_size;
	// int	endY = beginY - player->direction_line_size;
	double deltaX = endX - beginX; 
	double deltaY = endY - beginY; 
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX = deltaX / pixels; 
	deltaY = deltaY / pixels; 
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		// printf("pixelX=%f, pixelY=%f\n", pixelX, pixelY);
		// mlx_pixel_put(mlx, win, pixelX, pixelY, 0xFFFFFF);
		my_mlx_pixel_put(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return 0;
}

void	draw_game_board(t_win *win)
{
	// draw_borders(win->img);
	// draw_line_bresenham(400, 700, 500,500, win); - da ruim
	// draw_grid_lines(win);
	draw_map_walls(win->img, win->map);
	draw_player(win->img, win->player);
	draw_player_direction_line(win->img, win->player, win->player->x, win->player->y, BLUE);
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
	// mlx_pixel_put(win->mlx_ptr, win->win_ptr, 312, 312, 0xFF0000); por que não funciona???
}
