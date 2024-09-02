/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 11:23:21 by davifern         ###   ########.fr       */
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

// se eu mudo somente o y entao o player nao pode mover-se na diagonal
// o y no alto da tela vale 0 e no fim o HEIGTH
int	key_press_handler(int keycode, t_data *data)
{
	if (keycode == ESC_M || keycode == ESC_L)
		close_window(data);
	if (keycode == KEY_W_M || keycode == KEY_W_L)
		data->w = 1;
	else if (keycode == KEY_S_M || keycode == KEY_S_L)
		data->s = 1;
	else if (keycode == KEY_A_M || keycode == KEY_A_L)
		data->a = 1;
	else if (keycode == KEY_D_M || keycode == KEY_D_L) 
		data->d = 1;
	else if (keycode == KEY_RIGHT_M || keycode == KEY_RIGHT_L) 
		data->r = 1;
	else if (keycode == KEY_LEFT_M || keycode == KEY_LEFT_L)
		data->l = 1;
	render(data);
	return (0);
}

int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == KEY_W_M || keycode == KEY_W_L)
		data->w = 0;
	else if (keycode == KEY_S_M || keycode == KEY_S_L)
		data->s = 0;
	else if (keycode == KEY_A_M || keycode == KEY_A_L)
		data->a = 0;
	else if (keycode == KEY_D_M || keycode == KEY_D_L) 
		data->d = 0;
	else if (keycode == KEY_RIGHT_M || keycode == KEY_RIGHT_L) 
		data->r = 0;
	else if (keycode == KEY_LEFT_M || keycode == KEY_LEFT_L)
		data->l = 0;
	render(data);
	return 0;
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
	// mlx_hook(data->win_ptr, 2, 1L << 0, choose_event, data); //linux
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, key_release_handler, data);
}
