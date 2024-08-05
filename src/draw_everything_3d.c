/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/05 19:35:59 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: fazer o ceu e o solo
// void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
// {
//     Uint32 *pixels = (Uint32 *)surface->pixels;
//     pixels[(y * surface->w) + x] = pixel;
// }

void verLine(t_win *win, int pixelX, int y1, int y2)
{
    for (int pixelY = y1; pixelY <= y2; pixelY++)
    {
        // setPixel(surface, x, y, color);
        my_mlx_pixel_put(win->img, pixelX, pixelY, BLUE);
    }
}


void    draw_everything_3d(t_win *win)
{
    int x;
    t_player *player = win->player;
    t_map *map = win->map;

    /* declaracoes iniciais */
    //double posX = 22, posY = 12;  //x and y start position
    //double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0;
    double planeY = 0.66;

    /* recalculado no loop */
    float rayDirX;
    float rayDirY;
    double cameraX;
    int mapX;
	int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;

    int hit = 0;
    int side = 0;

    x = 0;
    while (x < WIDTH)
    {
printf("Aqui %d\n", x);
        cameraX = 2 * x / (double)WIDTH - 1;
        rayDirX = player->dir_x + planeX * cameraX;
        rayDirY = player->dir_y - planeY * cameraX;
        
        mapX = (int)player->x;
        mapY = (int)player->y;

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        

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
        if (rayDirY < 0)
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
            if (map->grid[mapY][mapX] == '1') //TODO: por que no do lodev eh mapX, mapY?
                hit = 1; 
        }
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else           perpWallDist = (sideDistY - deltaDistY);

        //height of the vertical line that should be drawn            
        int lineHeight = (int)(HEIGHT / perpWallDist); //You can of course also multiply it with another value, for example 2*screenHeight, if you want to walls to be higher or lower

        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        verLine(win, x, drawStart, drawEnd);
        x++;
    }
}