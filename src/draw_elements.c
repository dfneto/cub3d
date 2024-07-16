/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:29:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/16 11:02:38 by davifern         ###   ########.fr       */
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

void	draw_player_direction(t_img *img, t_player *player)
{
	int	y;
	y = player->y - player->size/2 - player->direction_line_size;
	while (y >= player->y - player->size/2 - player->direction_line_size 
		&& y <= player->y)
	{
		my_mlx_pixel_put(img, player->x, y, YELLOW);
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

void	draw_the_wall(t_img *img, int x_counter) // c 1
{
	(void)img;
	int x = x_counter * WALL_SIZE - WALL_SIZE; //0
	int y = 0; //counter * WALL_SIZE - WALL_SIZE; //0
	// int y = 382;
	while (y < WALL_SIZE) //64
	{		
		// printf("y=%d\n", y);								 
		while (x < x_counter * WALL_SIZE) //64
		{
			// printf("y=%d, x=%d\n", y, x);
			my_mlx_pixel_put(img, x, y, YELLOW);
			x++;
		}
		x = x_counter * WALL_SIZE - WALL_SIZE;
		y++;
	}
	printf("\n");	
}

void	draw_map_grid(t_img *img, t_map *map)
{

	(void) map;
	(void) img;
	// int i = 0;
	// int j = 0;

	draw_the_wall(img, 1);
	printf("indo para a próxima parede\n");
	draw_the_wall(img, 2);
	draw_the_wall(img, 3);
	draw_the_wall(img, 4);
	draw_the_wall(img, 5);
	draw_the_wall(img, 6);
	// if (map->grid[i][j] == '1')
	// 	draw_the_wall(img, j + 1);
	// // i = 2;
	// j = 1;
	// if (map->grid[i][j] == '1')
	// 	draw_the_wall(img, j + 1);
		
	// while (i < ROWS) //6
	// {
	// 	while (j < COLS) //6
	// 	{
	// 		if (map->grid[i][j] == '1')
	// 			// printf("1 ");
	// 			draw_the_wall(img, j + 1);
	// 		else
	// 			printf("0 ");
	// 		//	fill_black(img, counter);
	// 			//printf("%c ", map->grid[i][j]);
	// 		j++;
	// 	}
	// 	j = 0;
	// 	i++;
	// 	printf("\n");
	// }
}

void	draw_game_board(t_win *win)
{
//	draw_borders(win->img);
	draw_map_grid(win->img, win->map);
	draw_player(win->img, win->player);
	draw_player_direction(win->img, win->player);
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
}
