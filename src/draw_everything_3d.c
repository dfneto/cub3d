/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/12 13:49:25 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void verLine(t_win *win, int x, int y_start, int y_end, int color)
{
    int y = y_start;
    while (y <= y_end)
    {
        my_mlx_pixel_put(win->img, x, y, color);
        y++;
    }
}

void    draw_everything_3d(t_win *win)
{
    clean_map(win->img);
    t_player *player = win->player;
    t_map *grid_map = win->map;

    int x;
    double rayDirX = 0.0;
    double rayDirY = 0.0;
    double cameraX = 0.0;
    double deltaDistX = 0.0;
    double deltaDistY = 0.0;
    double sideDistX = 0.0;
    double sideDistY = 0.0;
    double perpWallDist = 0.0;
    int hit = 0;
    int mapX = 0;
    int mapY = 0;
    int stepX = 0;
    int stepY = 0;
    int side = 0;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int color;
    
    x = 0;
    while (x < WIDTH)
    {
        //zera tudo
        cameraX = 0.0;
        rayDirX = 0.0;
        rayDirY = 0.0;
        mapX = 0;
        mapY = 0;
        stepX = 0;
        stepY = 0;
        sideDistX = 0.0;
        sideDistY = 0.0;
        deltaDistX = 0.0;
        deltaDistY = 0.0;
        perpWallDist = 0.0;
        side = 0;
        hit = 0;
        lineHeight = 0;
        drawStart = 0;
        drawEnd = 0;

        cameraX = 2 * x / (double)WIDTH - 1;
        rayDirX = player->dir_x + player->planeX * cameraX;
        rayDirY = player->dir_y + player->planeY * cameraX;
        
        mapX = (int)player->pos_x;
        mapY = (int)player->pos_y;

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        // deltaDistX = fabs(1 / rayDirX);
        // deltaDistY = fabs(1 / rayDirY);

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player->pos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->pos_x) * deltaDistX; 
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player->pos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->pos_y) * deltaDistY;
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
            if (grid_map->grid[mapY][mapX] == '1')
            {
                hit = 1;
                color = BLUE;
            }
            if (grid_map->grid[mapY][mapX] == '2')
            {
                hit = 1; 
                color = RED;
            }
        }
        if (side == 0) //acho que entao bateu no lado do quadrado (W O)
            perpWallDist = (sideDistX - deltaDistX);
        else           //bateu em cima ou em baixo (N S)
            perpWallDist = (sideDistY - deltaDistY);

        //height of the vertical line that should be drawn            
        lineHeight = (int)(HEIGHT / perpWallDist); //You can of course also multiply it with another value, for example 2*screenHeight, if you want to walls to be higher or lower

        drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0) //quer dizer que começaria a desenhar fora da tela
            drawStart = 0;
        drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) //quer dizer que terminaria de desenhar fora da tela
            drawEnd = HEIGHT - 1;

        verLine(win, x, drawStart, drawEnd, color);
        x++;
    }
}
