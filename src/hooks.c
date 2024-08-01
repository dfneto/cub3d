/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/30 13:11:12 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
* hook.c have functions related to the hooks
*/
#include "cub3d.h"

int dda_collision_detection_old(t_map *map, float x_start, float y_start, float x_end, float y_end) {
	printf("---------------------------------------------------------------\n");
	int grid_x = (int)round(x_end);
	int grid_y = (int)round(y_end);
	// printf("Player is in grid [%d, %d] - y=%.2f, x=%.2f\n", (int)round(y_start), (int)round(x_start), y_start, x_start);
	printf("Player wants to go to [%d, %d] - y=%.2f, x=%.2f\n", grid_y, grid_x, y_end, x_end);
    // Calculate dx and dy
    float dx = x_end - x_start;
    float dy = y_end - y_start;
	printf("dx=%.f, dy=%2.f\n", dx, dy);
	
    // Determine the number of steps
    int steps = fmax(fabs(dx), fabs(dy));
	if (steps == 0) steps = 1;

    // Calculate the increment for each step
    float x_increment = dx / steps;
    float y_increment = dy / steps;
	printf("steps=%d, x_incremente=%.4f, y_increment=%4.f\n", steps, x_increment, y_increment);

    // Initialize starting points
    float x = x_start;
    float y = y_start;
    // Traverse the grid and check for collisions 
    for (int i = 0; i <= steps; i++) {
        int grid_x = (int)round(x);
        int grid_y = (int)round(y);
		// if (i == 0)	printf("Player is in grid [%d, %d]\n", grid_y, grid_x);
		// else 		printf("Next grid: [%d, %d]\n", grid_y, grid_x);

        // Check if the current position is within the grid bounds
        if (grid_x < 0 || grid_x >= COLS || grid_y < 0 || grid_y >= ROWS) {
            return 1;  // Out of bounds, treat as collision
        }

        // Check for collision with a wall (assuming '1' represents a wall)
		if (map->grid[grid_y][grid_x] == '1')
		{
			printf("Colision actual grid detect: [%d, %d] = %c\n", grid_y, grid_x, map->grid[grid_y][grid_x]);
            return 1;  // Collision detected
		}
        // if (map->grid[grid_y+(int)round(y_increment)][grid_x+(int)round(x_increment)] == '1') {
		// 	printf("Colision next grid detect: [%d, %d] = %c\n", grid_y+(int)round(y_increment), grid_x+(int)round(x_increment), map->grid[grid_y+(int)round(y_increment)][grid_x+(int)round(x_increment)]);
        //     return 1;  // Collision detected
        // }
		else 
			printf("Colision NOT detect: [%d, %d] = %c\n", grid_y, grid_x, map->grid[grid_y][grid_x]);

        // Move to the next point
        x += x_increment;
        y += y_increment;
		printf("Player moved to y=%.2f, x=%.2f\n", y, x);
		printf("Player is in grid [%d, %d]\n", (int)round(y), (int)round(x));
    }

    return 0;  // No collision detected
}

int	close_window(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	exit(0);
}

int FixAng(int a)
{ 
	if (a > 359)
		a = 0;
	if (a < 0)
		a = 360;
	return a;
}

float degToRad(int a) 
{ 
	return (a * M_PI) / 180.0;
}

int	choose_event(int keycode, t_win *win)
{
	double rotSpeed = 0.09;
	if (!win)
		return (1);
	if (keycode == ESC)
		close_window(win);
	if (keycode == KEY_A)
	{
		// win->player->x -= win->player->speed;
		win->player->x = (win->player->x - win->player->dir_y);// * win->player->speed;
		win->player->y = (win->player->y - win->player->dir_x);// * win->player->speed;
		// win->player->y -= win->player->speed;
		// win->player->y -= degToRad(win->player->angle) * win->player->speed;

	}
	if (keycode == KEY_D)
	{
		// if (!dda_collision_detection(win->map, win->player->x, win->player->y, win->player->x + win->player->dir_y, win->player->y + win->player->dir_x))
		// win->player->x += win->player->speed;
		win->player->x = (win->player->x + win->player->dir_y);// * win->player->speed;
		win->player->y = (win->player->y + win->player->dir_x);// * win->player->speed;
		// win->player->y += win->player->speed;
		// win->player->y += win->player->speed; //degToRad(win->player->angle) * win->player->speed;
	}
	if (keycode == KEY_W)
	{	
		double distance = dda_collision_detection_lodev(win->player, win->map).distance;
		//TODO: devo fazer alguma conta para fazer que quando suba ou desca va na mesma velocidade que para os lados
		// if (!dda_collision_detection(win->map, win->player->x, win->player->y, win->player->x + win->player->dir_x, win->player->y - win->player->dir_y))
		// if (!dda_collision_detection_lodev(win->player, win->map))
		// {
		if (distance > 0.5)
		{
			// posicion = posicion + vetor dir * speed
			win->player->x = win->player->x + win->player->dir_x * win->player->speed;
			win->player->y = win->player->y - win->player->dir_y * win->player->speed;
		}
		// }
		// int grid_x = (int)round(win->player->x);
        // int grid_y = (int)round(win->player->y);
		// printf("Player is in grid [%d, %d]\n", grid_y, grid_x);
		// win->player->y -= win->player->delta_y * win->player->speed; //se eu mudo somente o y entao o player nao pode mover-se na diagonal
		//o y no alto da tela vale 0 e no fim o HEIGTH
	}
	if (keycode == KEY_S)
	{
		// posicion = posicion - vetor dir * speed
		win->player->x = (win->player->x - win->player->dir_x);// * win->player->speed;
		win->player->y = (win->player->y + win->player->dir_y);// * win->player->speed;
		// int grid_x = (int)round(win->player->x);
        // int grid_y = (int)round(win->player->y);
		// printf("Player is in grid [%d, %d]\n", grid_y, grid_x);
	}
	if (keycode == KEY_LEFT)
	{
		double oldDirX = win->player->dir_x;
            win->player->dir_x = win->player->dir_x * cos(rotSpeed) - win->player->dir_y * sin(rotSpeed);
            win->player->dir_y = oldDirX * sin(rotSpeed) + win->player->dir_y * cos(rotSpeed);
		// win->player->dir_x = win->player->dir_x * cos(90) - win->player->dir_y * sin(90);
		// win->player->dir_y = win->player->dir_x * sin(90) - win->player->dir_y * cos(90);
		// x = x * cs(-5) - y * sn; // now x is something different than original vector x
		// y = x * sn + y * cs;
	}
	if (keycode == KEY_RIGTH)
	{
		double oldDirX = win->player->dir_x;
		win->player->dir_x = win->player->dir_x * cos(-rotSpeed) - win->player->dir_y * sin(-rotSpeed);
            win->player->dir_y = oldDirX * sin(-rotSpeed) + win->player->dir_y * cos(-rotSpeed);
		// printf("Antes: dir x: %f, dir y: %f\n", win->player->dir_x, win->player->dir_y);
		// win->player->dir_x = win->player->dir_x * cos(5) + win->player->dir_y * sin(5);
		// win->player->dir_y = win->player->dir_x * sin(5) + win->player->dir_y * cos(5);
		// printf("Depois: dir x: %f, dir y: %f\n", win->player->dir_x, win->player->dir_y);
		// x = x * cs(+5) - y * sn; // now x is something different than original vector x
		// y = x * sn + y * cs;
	}
	draw_game_board(win);
	// printf("Keycode: %d\n", keycode);
	return (0);
}

int	close_window_mouse(t_win *win)
{
	if (win)
		close_window(win);
	return (0);
}

/* 
Entendo que ao pressionarmos uma tecla lançamos o evento int 2 e ao 
clicarmos no x da janela com o mouse o evento 17
*/
void	set_hooks(t_win *win)
{
	// t_img	*img = NULL;
	mlx_hook(win->win_ptr, 17, 0, close_window_mouse, win);
	//mlx_hook(win->win_ptr, 2, 0, choose_event, win); //equivalente a mlx_key_hook(win->win_ptr, choose_event, win); //mac
	mlx_hook(win->win_ptr, 2, 1L << 0, choose_event, win); //linux
}
