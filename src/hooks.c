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
		if (is_player_inside_the_borders_map(player))
		{
			player->x = player->x - player->dir_y * PLAYER_SPEED;
			player->y = player->y - player->dir_x * PLAYER_SPEED;
		}
	}
	if (keycode == KEY_D)
	{
		player->x = player->x + player->dir_y * PLAYER_SPEED;
		player->y = player->y + player->dir_x * PLAYER_SPEED;
	}
	if (keycode == KEY_W)
	{	
		if (!has_wall(player))
		{
			// posicion = posicion + vetor_dir * speed
			player->x = player->x + player->dir_x * PLAYER_SPEED; //lodev: if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
			player->y = player->y - player->dir_y * PLAYER_SPEED;
		}
		// se eu mudo somente o y entao o player nao pode mover-se na diagonal
		// o y no alto da tela vale 0 e no fim o HEIGTH
	}
	if (keycode == KEY_S)
	{
		// posicion = posicion - vetor dir * speed
		player->x = player->x - player->dir_x * PLAYER_SPEED;
		player->y = player->y + player->dir_y * PLAYER_SPEED;
	}

	// x = x * cs(ang) - y * sn(ang); // ang eh o angulo que quero rotacionar
	// y = x * sn(ang) + y * cs(ang);
	if (keycode == KEY_LEFT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y * sin(ROT_SPEED);
		player->dir_y = oldDirX * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
	}
	if (keycode == KEY_RIGTH)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y * sin(-ROT_SPEED);
		player->dir_y = oldDirX * sin(-ROT_SPEED) + player->dir_y * cos(-ROT_SPEED);
	}
	draw_everything(player->win);
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
