/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/08/22 13:22:09 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
* hook.c have functions related to the hooks
*/
#include "cub3d.h"

int	close_window(t_data *data)
{
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	choose_event(int keycode, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (keycode == ESC)
		close_window(data);
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
	render(data);
	return (0);
}

/* 
Entendo que ao pressionarmos uma tecla lançamos o evento int 2 e ao 
clicarmos no x da janela com o mouse o evento 17
*/
void	set_hooks(t_data *data)
{
	//TODO: ver como eh possivel pressionar a direcao junto com os movimentos
	mlx_hook(data->win_ptr, 33, 0, close_window, data);
	//mlx_hook(win->win_ptr, 2, 0, choose_event, win); //equivalente a mlx_key_hook(win->win_ptr, choose_event, win); //mac
	mlx_hook(data->win_ptr, 2, 1L << 0, choose_event, data); //linux
}
