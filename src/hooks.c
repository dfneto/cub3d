/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:37:30 by davifern          #+#    #+#             */
/*   Updated: 2024/07/08 13:29:02 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
* hook.c have functions related to the hooks
*/
#include "cub3d.h"

int	move_to_left(t_img *img, int step)
{
	int		x;
	int		y;
	t_win	*win;

	x = 0;
	y = 0;
	win = img->win;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			//make the map borders
			if ((x > 490 || x < 10) || (y > 490 || y < 10))
				my_mlx_pixel_put(img, x, y, YELLOW);
			
			//make the player 10x10 pxl
			if ((x > 64 - step && x < 74 - step) && (y > 340 - step && y < 350 - step))
				my_mlx_pixel_put(img, x, y, RED);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	choose_event(int keycode, t_win *win)
{
	if (keycode == ESC && win)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		exit(0);
	}
	if (keycode == 0)
	{
		move_to_left(win->img, 5);
		return (0);
	}
	printf("Keycode: %d\n", keycode);
	return (0);
}

int	close_window_mouse(t_win *win)
{
	if (win)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		exit(0);
	}
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
    mlx_key_hook(win->win_ptr, choose_event, win); // equivalente a mlx_hook(win->win_ptr, 2, 0, close_window, win);
}
