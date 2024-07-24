/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/24 19:00:32 by davifern         ###   ########.fr       */
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
	if (!win)
		return (1);
	if (keycode == ESC)
		close_window(win);
	if (keycode == KEY_A)
	{
		win->player->x -= win->player->speed;
		// win->player->y -= win->player->speed;
		// win->player->y -= degToRad(win->player->angle) * win->player->speed;

	}
	if (keycode == KEY_D)
	{
		win->player->x += win->player->speed;
		// win->player->y += win->player->speed;
		// win->player->y += win->player->speed; //degToRad(win->player->angle) * win->player->speed;
	}
	if (keycode == KEY_W)
	{	//TODO: devo fazer alguma conta para fazer que quando suba ou desca va na mesma velocidade que para os lados
		// posicion = posicion + vetor dir * speed
		win->player->x = (win->player->x + win->player->dir_x);// * win->player->speed;
		win->player->y = (win->player->y - win->player->dir_y);// * win->player->speed;
		
		// win->player->y -= win->player->delta_y * win->player->speed; //se eu mudo somente o y entao o player nao pode mover-se na diagonal
		//o y no alto da tela vale 0 e no fim o HEIGTH
	}
	if (keycode == KEY_S)
	{
		// posicion = posicion - vetor dir * speed
		win->player->x = (win->player->x - win->player->dir_x);// * win->player->speed;
		win->player->y = (win->player->y + win->player->dir_y);// * win->player->speed;
	}
	if (keycode == KEY_LEFT)
	{
		win->player->dir_x = win->player->dir_x * cos(90) - win->player->dir_y * sin(90);
		win->player->dir_y = win->player->dir_x * sin(90) - win->player->dir_y * cos(90);
		// x = x * cs(-5) - y * sn; // now x is something different than original vector x
		// y = x * sn + y * cs;
	}
	if (keycode == KEY_RIGTH)
	{
		printf("Antes: dir x: %f, dir y: %f\n", win->player->dir_x, win->player->dir_y);
		win->player->dir_x = win->player->dir_x * cos(5) + win->player->dir_y * sin(5);
		win->player->dir_y = win->player->dir_x * sin(5) + win->player->dir_y * cos(5);
		printf("Depois: dir x: %f, dir y: %f\n", win->player->dir_x, win->player->dir_y);
		// x = x * cs(+5) - y * sn; // now x is something different than original vector x
		// y = x * sn + y * cs;
	}
	draw_game_board(win);
	printf("Keycode: %d\n", keycode);
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
