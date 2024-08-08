/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/08 11:16:26 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: fazer o ceu e o solo
void verLine(t_win *win, int x, int y_start, int y_end)
{
    // printf("PixelX = %d, y1 = %d, y2=%d\n", x, y_start, y_end);
    int y = y_start;
    while (y <= y_end)
    {
        my_mlx_pixel_put(win->img, x, y, BLUE);
        y++;
    }
    mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
}


void    draw_everything_3d(t_win *win)
{
    clean_map(win->img);
    int x;
    t_player *player = win->player;
    t_map *map = win->map;

    /* declaracoes iniciais */
    //double dirX = -1, dirY = 0; //initial direction vector
    // player.dir_x = -1;
    // player.dir_y = 0;
    // printf("dirX: %f, dirY=%f\n", player->dir_x, player->dir_y);
    // player->planeX = 0;
    // player->planeY = 0.66;
    double planeX = player->planeX;
    double planeY = player->planeY;
    /* recalculado no loop */
    float rayDirX = 0;
    float rayDirY = 0;
    double cameraX = 0;
    int mapX = 0;
	int mapY = 0;
    double deltaDistX = 0;
    double deltaDistY = 0;
    int hit = 0;

    x = 0;
    while (x < WIDTH)
    {
        hit = 0;
        cameraX = 2 * x / (double)WIDTH - 1;
        rayDirX = player->dir_x + planeX * cameraX;
        rayDirY = player->dir_y + planeY * cameraX;
        
        mapX = (int)player->x;
        mapY = (int)player->y;

        double sideDistX;
        double sideDistY;
        
        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        
        double perpWallDist;
        int stepX;
        int stepY;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player->x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->x) * deltaDistX;
        }
        if (rayDirY > 0)
        {
            stepY = -1;
            sideDistY = (player->y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->y) * deltaDistY;
        }

        while (hit == 0) //enquanto não bateu na parede
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map->grid[mapY][mapX] == '1')
                hit = 1; 
        }
        if (side == 0) //acho que entao bateu no lado do quadrado (W O)
            perpWallDist = (sideDistX - deltaDistX);
        else           //bateu em cima ou em baixo (N S)
            perpWallDist = (sideDistY - deltaDistY);

        //height of the vertical line that should be drawn            
        int lineHeight = (int)(HEIGHT / perpWallDist); //You can of course also multiply it with another value, for example 2*screenHeight, if you want to walls to be higher or lower

        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0) //quer dizer que começaria a desenhar fora da tela
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) //quer dizer que terminaria de desenhar fora da tela
            drawEnd = HEIGHT - 1;

        verLine(win, x, drawStart, drawEnd);
        x++;
    }
}