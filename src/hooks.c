/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/08/13 09:34:57 by davifern         ###   ########.fr       */
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
	if (keycode == KEY_W)
	{	
		player->pos_x += player->dir_x * PLAYER_SPEED; //lodev: if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
		player->pos_y += player->dir_y * PLAYER_SPEED;
		// se eu mudo somente o y entao o player nao pode mover-se na diagonal
		// o y no alto da tela vale 0 e no fim o HEIGTH
	}
	if (keycode == KEY_S)
	{
		// posicion = posicion - vetor_dir * speed
		player->pos_x -= player->dir_x * PLAYER_SPEED;
		player->pos_y -= player->dir_y * PLAYER_SPEED;
	}
	if (keycode == KEY_D)
	{
		player->pos_x = player->pos_x + player->dir_y * PLAYER_SPEED;
		player->pos_y = player->pos_y - player->dir_x * PLAYER_SPEED;
	}
	if (keycode == KEY_A)
	{
		player->pos_x = player->pos_x - player->dir_y * PLAYER_SPEED;
		player->pos_y = player->pos_y + player->dir_x * PLAYER_SPEED;
	}
	// x = x * cs(ang) - y * sn(ang); // ang eh o angulo que quero rotacionar
	// y = x * sn(ang) + y * cs(ang);
	if (keycode == KEY_RIGTH)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y * sin(-ROT_SPEED);
		player->dir_y = oldDirX * sin(-ROT_SPEED) + player->dir_y * cos(-ROT_SPEED);
		double oldPlaneX = player->planeX; //a direcao do jogador (acima) e a do plano sao rotacionadas
		player->planeX = player->planeX * cos(-ROT_SPEED) - player->planeY * sin(-ROT_SPEED);
		player->planeY = oldPlaneX * sin(-ROT_SPEED) + player->planeY * cos(-ROT_SPEED);
	}
	if (keycode == KEY_LEFT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y * sin(ROT_SPEED);
		player->dir_y = oldDirX * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
		double oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(ROT_SPEED) - player->planeY * sin(ROT_SPEED);
		player->planeY = oldPlaneX * sin(ROT_SPEED) + player->planeY * cos(ROT_SPEED);
	}
	draw_everything_3d_texture(player->win);
	draw_minimap(player->win);
	mlx_put_image_to_window(player->win->mlx_ptr,
			player->win->win_ptr, player->win->img->img_ptr, 0, 0);
	
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
	mlx_hook(win->win_ptr, 33, 0, close_window_mouse, win);
	//mlx_hook(win->win_ptr, 2, 0, choose_event, win); //equivalente a mlx_key_hook(win->win_ptr, choose_event, win); //mac
	mlx_hook(win->win_ptr, 2, 1L << 0, choose_event, win->player); //linux
}
