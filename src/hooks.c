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

int	close_window(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	exit(0);
}

int	choose_event(int keycode, t_player *player)
{
	if (!player->win)
		return (1);
	if (keycode == ESC)
		close_window(player->win);
	if (keycode == KEY_A)
	{
		// player->x -= player->speed;
		player->x = (player->x - player->dir_y);// * player->speed;
		player->y = (player->y - player->dir_x);// * player->speed;
		// player->y -= player->speed;
		// player->y -= degToRad(player->angle) * player->speed;
	}
	if (keycode == KEY_D)
	{
		// if (!dda_collision_detection(win->map, player->x, player->y, player->x + player->dir_y, player->y + player->dir_x))
		// player->x += player->speed;
		player->x = (player->x + player->dir_y);// * player->speed;
		player->y = (player->y + player->dir_x);// * player->speed;
		// player->y += player->speed;
		// player->y += player->speed; //degToRad(player->angle) * player->speed;
	}
	if (keycode == KEY_W)
	{	
		//TODO: devo fazer alguma conta para fazer que quando suba ou desca va na mesma velocidade que para os lados
		// if (!dda_collision_detection(win->map, player->x, player->y, player->x + player->dir_x, player->y - player->dir_y))
		// if (!dda_collision_detection_lodev(player, win->map))
		// {
		if (!has_wall(player))
		{
			// posicion = posicion + vetor dir * speed
			player->x = player->x + player->dir_x * player->speed;
			player->y = player->y - player->dir_y * player->speed;
		}
		// }
		// int grid_x = (int)round(player->x);
        // int grid_y = (int)round(player->y);
		// printf("Player is in grid [%d, %d]\n", grid_y, grid_x);
		// player->y -= player->delta_y * player->speed; //se eu mudo somente o y entao o player nao pode mover-se na diagonal
		//o y no alto da tela vale 0 e no fim o HEIGTH
	}
	if (keycode == KEY_S)
	{
		// posicion = posicion - vetor dir * speed
		player->x = (player->x - player->dir_x);// * player->speed;
		player->y = (player->y + player->dir_y);// * player->speed;
		// int grid_x = (int)round(player->x);
        // int grid_y = (int)round(player->y);
		// printf("Player is in grid [%d, %d]\n", grid_y, grid_x);
	}
	if (keycode == KEY_LEFT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y * sin(ROT_SPEED);
		player->dir_y = oldDirX * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
		// player->dir_x = player->dir_x * cos(90) - player->dir_y * sin(90);
		// player->dir_y = player->dir_x * sin(90) - player->dir_y * cos(90);
		// x = x * cs(-5) - y * sn; // now x is something different than original vector x
		// y = x * sn + y * cs;
	}
	if (keycode == KEY_RIGTH)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y * sin(-ROT_SPEED);
		player->dir_y = oldDirX * sin(-ROT_SPEED) + player->dir_y * cos(-ROT_SPEED);
		// printf("Antes: dir x: %f, dir y: %f\n", player->dir_x, player->dir_y);
		// player->dir_x = player->dir_x * cos(5) + player->dir_y * sin(5);
		// player->dir_y = player->dir_x * sin(5) + player->dir_y * cos(5);
		// printf("Depois: dir x: %f, dir y: %f\n", player->dir_x, player->dir_y);
		// x = x * cs(+5) - y * sn; // now x is something different than original vector x
		// y = x * sn + y * cs;
	}
	draw_game_board(player->win);
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
	mlx_hook(win->win_ptr, 17, 0, close_window_mouse, win);
	//mlx_hook(win->win_ptr, 2, 0, choose_event, win); //equivalente a mlx_key_hook(win->win_ptr, choose_event, win); //mac
	mlx_hook(win->win_ptr, 2, 1L << 0, choose_event, win->player); //linux
}
