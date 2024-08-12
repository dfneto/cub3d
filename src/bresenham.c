/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:09:37 by davifern          #+#    #+#             */
/*   Updated: 2024/08/12 11:15:49 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)

/* Esse arquivo eh usado somente para fazer as linhas brancas do map */

//x, y, x1, y1: são as linhas e colunas (coordenadas os 0s e 1s) do grid map
// draw_line_bresenham(700, 400, 500,500, win); - da ruim
// draw_line_bresenham(400, 700, 500,500, win); - da ruim
void draw_line_bresenham(float x, float y, float x1, float y1, t_win *win)//(1:1) (3:12)
{
    float x_step;
    float y_step;
    int max;
	int	zoom = 32;

	// ao multiplicar pelo zoom eu saio do mundo de linhas e colunas do grid map (coordenadas do grid map) e vou para o mundo de pixels
	// que serão preenchidos no while abaixo step por step (step=1)
	x *= zoom;
	y *= zoom;
	x1 *= zoom;
	y1 *= zoom;
    
	x_step = x1 - x;
    y_step = y1 - y;

    max = MAX(MOD(x_step), MOD(y_step));
    x_step /= max;
    y_step /= max;

	//para cada linha na horizontal e vertical, vai pixel por pixel
    while ((int) (x - x1) || (int) (y - y1))
    {
		my_mlx_pixel_put(win->img, x, y, 0xffffff);
        x += x_step;
        y += y_step;
    }
}

//TODO: imprimo a borda da esquerda e de cima, mas não a da direita e de baixo
void	draw_grid_lines(t_win *win)
{
	int	x;
	int	y;

	y = 0;
	while (y < win->height)
	{
		x = 0;
		while (x < win->width)
		{
			draw_line_bresenham(x, y, x + 1, y, win);//[0 0] [1 0]
			draw_line_bresenham(x, y, x, y + 1, win); //[0 0] [0 1]
			x++;
		}
		y++;
	}
}