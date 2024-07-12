/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/11 10:51:09 by davifern         ###   ########.fr       */
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

int	choose_event(int keycode, t_win *win)
{
	if (!win)
		return (1);
	if (keycode == ESC)
		close_window(win);
	if (keycode == KEY_A)
		win->player->x -= win->player->speed;
	if (keycode == KEY_D)
		win->player->x += win->player->speed;
	if (keycode == KEY_W)
		win->player->y -= win->player->speed; //o y no alto da tela vale 0 e no fim o HEIGTH
	if (keycode == KEY_S)
		win->player->y += win->player->speed;
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
